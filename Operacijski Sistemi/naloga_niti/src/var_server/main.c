#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "definitions.h"
#include "threading.h"
#include "variable_list_struct.h"
#include "variable_struct.h"

bool stop_sig=false;
static void
server_stop_handler(int signum){
   stop_sig=true; 
}

static void
send_response_and_shared_memory(int data_socket, char response[], int shm_fd)
{
    // Send shared memory name and file descriptor over unix socket
    struct iovec msg_io = { 0 };
    msg_io.iov_base = response;
    msg_io.iov_len = strlen(response) + 1;

    struct msghdr msg = { 0 };
    msg.msg_iov = &msg_io;
    msg.msg_iovlen = 1;

    char fd_buf[CMSG_SPACE(sizeof(shm_fd))] = { 0 };
    msg.msg_control = fd_buf;
    msg.msg_controllen = sizeof(fd_buf);

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(shm_fd));
    *((int *) CMSG_DATA(cmsg)) = shm_fd;

    ssize_t n = sendmsg(data_socket, &msg, 0);
    if (n == -1) {
        perror("ERROR (send_response_and_shared_memory, sendmsg)");
    }
}

static bool
check_error(int value, const char msg[])
{
    if (value == -1) {
        // TODO you can replace this using printf and strerror
        char buf[MAX_ERROR_LEN];
        snprintf(buf, sizeof(buf), "ERROR (%s)", msg);
        perror(buf);
        return true;
        //exit(EXIT_FAILURE); we don't really want to just exit on an any error
    }
    return false;
}

static int
create_connection()
{   
    int connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    check_error(connection_socket, "socket");

    struct sockaddr_un socket_addr = { 0 };
    socket_addr.sun_family = AF_UNIX;
    strncpy(socket_addr.sun_path, SOCKET_PATH, sizeof(socket_addr.sun_path) - 1);
    
    int ret = bind(connection_socket, (struct sockaddr *) &socket_addr, sizeof(socket_addr));
    check_error(ret, "bind");

    ret = listen(connection_socket, CONNECTION_QUEUE_SIZE);
    check_error(ret, "listen");

    return connection_socket;
}

static void
destroy_connection(int connection_socket)
{
    int ret = close(connection_socket);
    check_error(ret, "close");

    ret = unlink(SOCKET_PATH);
    check_error(ret, "unlink");
}


static void
send_response(int data_socket, char *response){
    struct iovec msg_io = { 0 };
    msg_io.iov_base = response;
    msg_io.iov_len = strlen(response) + 1;


    struct msghdr msg = { 0 };
    msg.msg_iov = &msg_io;
    msg.msg_iovlen = 1;

    ssize_t n = sendmsg(data_socket, &msg, 0);
    if (n == -1) {
        perror("ERROR (send_response, sendmsg)");
        //exit(EXIT_FAILURE);
    }
}

static void
get_variable_locked(struct variable_struct* var_obj, void* args);
static void
get_variable(int data_socket, const char var_name[], struct variables_list_struct *var_list_obj) 
{
    // find variable
    struct variable_struct *var_obj = find_named_variable(var_list_obj, var_name);
    if(var_obj==NULL){
        send_response(data_socket, "FAIL");
        return;
    }

    read_variable_lock(var_obj, get_variable_locked, &data_socket);
}

static void
get_variable_locked(struct variable_struct* var_obj, void* args){
    int data_socket=*(int*)args;

    // open resource shared memory
    int shm_fd = open("./", O_RDWR|__O_TMPFILE, 0660);
    if(shm_fd==-1){
        // if resource doesn't exists
        // send error message
        perror("could not create temporary resource");
        send_response(data_socket, "FAIL");
    }
    write(shm_fd, var_obj->data, 4096);

    // change the file descriptor to READ ONLY
    fcntl(shm_fd, F_SETFD, F_SETFL, O_RDONLY);

    send_response_and_shared_memory(data_socket, "OK", shm_fd);
    // should receive a done, release the variable access
    char response[MAX_REQUEST_LEN]="";
    recv(data_socket, response, sizeof(response), 0);
    if(strcmp(response, "DONE") != 0)
    {
        printf("ISSUE: set_resource, no DONE received\n");
    }

    // Close resource shared memory
    int ret = close(shm_fd);
    check_error(ret, "close");
}


static void
set_variable_locked(struct variable_struct *var_obj, void* args);
static void
set_variable(int data_socket, const char var_name[], struct variables_list_struct *var_list_obj)
{
    // check if resource is registered and available
    printf("looking for: %s\n", var_name);
    struct variable_struct *var_obj = find_named_variable(var_list_obj, var_name);
    if(var_obj==NULL){
        printf("creating new variable: %s\n", var_name);
        var_obj = create_new_variable(var_list_obj, var_name);
    }

    write_variable_lock(var_obj, set_variable_locked, &data_socket);
}

static void
set_variable_locked(struct variable_struct *var_obj, void* args)
{
    int data_socket=*(int*)args;

    // open resource shared memory
    int shm_fd = open("./", O_RDWR|__O_TMPFILE, 0660);
    if(shm_fd==-1){
        // if resource doesn't exists
        // send error message
        perror("could not create temporary resource");
        send_response(data_socket, "FAIL");
    }
    ftruncate(shm_fd, 4096);

    send_response_and_shared_memory(data_socket, "OK", shm_fd);
    char response[MAX_REQUEST_LEN]="";
    recv(data_socket, response, sizeof(response), 0);
    if(strcmp(response, "DONE") != 0)
    {
        printf("ISSUE: set_resource, no DONE received\n");
    } else {
        // read the changes back to variable 
        read(shm_fd, var_obj->data, 4096);
    }

    // Close resource shared memory
    int ret = close(shm_fd);
    check_error(ret, "close");
}

static void
unset_variable(int data_socket, const char var_name[], struct variables_list_struct *var_list_obj)
{
    // check if resource is registered and available
    int ret_val = remove_named_variable(var_list_obj, var_name);
    if(ret_val==0){
        send_response(data_socket, "OK");
    } else {
        send_response(data_socket, "FAIL");
    }
    // should receive a done, release the variable access
    char response[MAX_REQUEST_LEN]="";
    recv(data_socket, response, sizeof(response), 0);
    if(strcmp(response, "DONE") != 0)
    {
        printf("ISSUE: set_resource, no DONE received\n");
    }
}

static void 
wait_for_change(int data_socket, const char var_name[], struct variables_list_struct *var_list_obj)
{
    // blocks if anyone is SET-ing this resource
    // wait for change
    struct variable_struct *var_obj = find_named_variable(var_list_obj, var_name);
    if(var_obj==NULL){
        send_response(data_socket, "FAIL");
        return;
    }
    send_response(data_socket, "OK");
    if(wait_variable_lock(var_obj)==0){
        send_response(data_socket, "WAS SET");
    } else {
        send_response(data_socket, "WAS UNSET");
    }
    char response[MAX_REQUEST_LEN]="";
    recv(data_socket, response, sizeof(response), 0);
    if(strcmp(response, "DONE") != 0)
    {
        printf("ISSUE: set_resource, no DONE received\n");
    }
}

struct client_handler_args{
    int data_socket;
    struct variables_list_struct *var_list_obj;
};
void
client_handler(void* args_void){
    struct client_handler_args* args=args_void;
    int data_socket = args->data_socket;
    struct variables_list_struct * var_list_obj = args->var_list_obj;
    free(args);

    ssize_t n;
    char request[MAX_REQUEST_LEN]="";
    char var_name[MAX_NAME_LEN]="";

    // create new thread here
    // run the following code
    n = recv(data_socket, request, sizeof(request), 0);
    if (n == -1) {
        perror("ERROR (main, recv, 1)");
        //exit(EXIT_FAILURE);
    }
    n = recv(data_socket, var_name, sizeof(request), 0);
    if (n == -1) {
        perror("ERROR (main, recv, 2)");
        //exit(EXIT_FAILURE);
    }

    printf("%s za %s\n", request, var_name);
    if (strcmp(request, "SET") == 0) { 
        set_variable(data_socket, var_name, var_list_obj); // blocks if anyone is SET or GET-ing this resource
    } else if (strcmp(request, "UNSET") == 0) {
        unset_variable(data_socket, var_name, var_list_obj); 
    } else if (strcmp(request, "GET") == 0) {
        get_variable(data_socket, var_name, var_list_obj); // blocks if anyone is SET-ing this resource
    } else if (strcmp(request, "WAIT") == 0){
        wait_for_change(data_socket, var_name, var_list_obj); // wait for someone to change (SET, UNSET) this resource
    }

    int ret = close(data_socket);
    check_error(ret, "close");
}

int
main()
{
    struct sigaction sa_conf;
    memset(&sa_conf, 0, sizeof(struct sigaction));
    sa_conf.sa_handler=server_stop_handler;
    sigemptyset(&sa_conf.sa_mask);
    sigaction(SIGINT, &sa_conf, NULL);
    sigaction(SIGTERM, &sa_conf, NULL);

    int connection_socket = create_connection();

    struct threading_struct threading_obj;
    threading_setup(&threading_obj);

    struct variables_list_struct var_list_obj;
    memset(&var_list_obj, 0, sizeof(struct variables_list_struct));
    init_variables_list(&var_list_obj);

    bool is_running = true;
    while (is_running) {
        if(stop_sig){
            is_running=false;
            continue;
        }
        int data_socket = accept(connection_socket, NULL, NULL);
        check_error(data_socket, "accept");

        struct client_handler_args *ch_args = malloc(sizeof(struct client_handler_args));
        ch_args->data_socket = data_socket;
        ch_args->var_list_obj = &var_list_obj;
        handle_in_thread(&threading_obj, client_handler, (void*)ch_args);
    }

    printf("shutting down, clearing variables list\n");
    destroy_connection(connection_socket);
    clear_variables_list(&var_list_obj);
    threading_cleanup(&threading_obj);

    return EXIT_SUCCESS;
}
