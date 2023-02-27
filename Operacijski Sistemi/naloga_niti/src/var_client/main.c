#include <fcntl.h>
#include <getopt.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <pthread.h>

#define READ_WRITE_BUF_SIZE 128
#define MAX_ERROR_LEN 128
#define MAX_RESPONSE_LEN 128
#define SOCKET_PATH "os.socket"

#define DONE 0 
#define ERR_VAR_MISSING 1 
#define ERR_VAR_CREATE 2 
#define WAIT_VAR_SET 3
#define WAIT_VAR_UNSET 4
#define ERR_TIMEOUT 5
#define ERR_CMD_PARAMS 128

static void
check_error(int value, const char msg[])
{
    if (value == -1) {
        char buf[MAX_ERROR_LEN];
        snprintf(buf, sizeof(buf), "ERROR (%s)", msg);
        perror(buf);
        exit(EXIT_FAILURE);
    }
}

static void
check_error_ssize(ssize_t value, const char msg[])
{
    if (value == -1) {
        char buf[MAX_ERROR_LEN];
        snprintf(buf, sizeof(buf), "ERROR (%s)", msg);
        perror(buf);
        exit(EXIT_FAILURE);
    }
}

static int
create_connection()
{
    int data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    check_error(data_socket, "socket");

    struct sockaddr_un socket_addr = { 0 };
    socket_addr.sun_family = AF_UNIX;
    strncpy(socket_addr.sun_path, SOCKET_PATH, sizeof(socket_addr.sun_path) - 1);
    
    int ret = connect(data_socket, (struct sockaddr *) &socket_addr, sizeof(socket_addr));
    check_error(ret, "connect");

    return data_socket;
}

static void
destroy_connection(int data_socket)
{
    int ret = close(data_socket);
    check_error(ret, "close");
}
static void
send_msg(int data_socket, const char msg[])
{
    ssize_t n = send(data_socket, msg, strlen(msg) + 1, 0);
    check_error_ssize(n, "send");
}

static void
get_response_and_shared_memory(int data_socket, char* response, int *shm_fd)
{
    // Read shared memory name and file descriptor from unix socket
    struct iovec msg_io = { 0 };
    msg_io.iov_base = response;
    msg_io.iov_len = MAX_RESPONSE_LEN;

    struct msghdr msg = { 0 };
    msg.msg_iov = &msg_io;
    msg.msg_iovlen = 1;

    char fd_buf[CMSG_SPACE(sizeof(shm_fd))] = { 0 };
    msg.msg_control = fd_buf;
    msg.msg_controllen = sizeof(fd_buf);

    ssize_t n = recvmsg(data_socket, &msg, 0);
    check_error_ssize(n, "recvmsg");

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    if(cmsg != NULL){
        *shm_fd = *((int *) CMSG_DATA(cmsg));
    } else {
        *shm_fd = -1;
    }
}

static void
open_and_write_shm(int shm_fd){
    char *shm = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) {
        perror("ERROR (open_and_write_shm, mmap)");
        exit(EXIT_FAILURE);
    }
    int l = read(0, shm, 4096);
    if(l<0){
        perror("ERROR (open_and_write_shm, read)");
        exit(EXIT_FAILURE);
    }
    shm[l] = 0;
}

static void
open_and_read_shm(int shm_fd){
    char *shm = mmap(NULL, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) {
        perror("ERROR (open_and_write_shm, mmap)");
        exit(EXIT_FAILURE);
    }
    int write_out=strlen(shm);
    if(write_out>4096){
        write_out=4096;
    }
    int l = write(1, shm, write_out);
    if(l<0){
        perror("ERROR (open_and_read_shm, write)");
        exit(EXIT_FAILURE);
    }
}
static int
set_variable(int data_socket, char* var_name, int delay_ms)
{
    printf("setting variable %s \n", var_name);
    // send request
    send_msg(data_socket, "SET");
    send_msg(data_socket, var_name);
    char response[MAX_RESPONSE_LEN]={0};
    int shm_fd=0;
    // get response
    get_response_and_shared_memory(data_socket, response, &shm_fd); 
    if(strcmp(response, "OK")==0){
        open_and_write_shm(shm_fd);
        usleep(delay_ms*1000);
        send_msg(data_socket, "DONE");
        return DONE;
    }else
    if(strcmp(response, "FAIL")==0){
        return ERR_VAR_CREATE;
    }else{
        printf("unrecognized response: %s\n", response);
        exit(EXIT_FAILURE);
    }
}

static int
unset_variable(int data_socket, char* var_name, int delay_ms)
{
    printf("removing variable %s \n", var_name);
    send_msg(data_socket, "UNSET");
    send_msg(data_socket, var_name);
    char response[MAX_RESPONSE_LEN]={0};
    int shm_fd=0;
    get_response_and_shared_memory(data_socket, response, &shm_fd); 
    if(strcmp(response, "OK")==0){
        usleep(delay_ms*1000);
        send_msg(data_socket, "DONE");
        return DONE;
    }else
    if(strcmp(response, "FAIL")==0){
        return ERR_VAR_MISSING;
    }else{
        printf("unrecognized response: %s\n", response);
        exit(EXIT_FAILURE);
    }
}

static int
get_variable(int data_socket, char* var_name, int delay_ms)
{
    printf("getting variable %s \n", var_name);
    send_msg(data_socket, "GET");
    send_msg(data_socket, var_name);

    char response[MAX_RESPONSE_LEN]={0};
    int shm_fd=0;
    get_response_and_shared_memory(data_socket, response, &shm_fd); 
    if(strcmp(response, "OK")==0){
        open_and_read_shm(shm_fd);
        usleep(delay_ms*1000);
        send_msg(data_socket, "DONE");
        return DONE;
    }else
    if(strcmp(response, "FAIL")==0){
        return ERR_VAR_MISSING;
    }else{
        printf("unrecognized response: %s\n", response);
        exit(EXIT_FAILURE);
    }
}

static int
wait_variable(int data_socket, char* var_name, int delay_ms)
{
    printf("waiting for change of variable %s \n", var_name);
    send_msg(data_socket, "WAIT");
    send_msg(data_socket, var_name);

    char response[MAX_RESPONSE_LEN]={0};
    int shm_fd=0;
    get_response_and_shared_memory(data_socket, response, &shm_fd); 
    if(strcmp(response, "OK")==0){
        get_response_and_shared_memory(data_socket, response, &shm_fd); 
        if(strcmp(response, "WAS SET")==0){
            printf("variable %s was set\n", var_name);
            return WAIT_VAR_SET;
        }else
        if(strcmp(response, "WAS UNSET")==0){
            printf("variable %s was unset\n", var_name);
            return WAIT_VAR_UNSET;
        }else{
            printf("unrecognized wait response: %s\n", response);
            exit(EXIT_FAILURE);
        }
        send_msg(data_socket, "DONE");
        return DONE;
    }else
    if(strcmp(response, "FAIL")==0){
        return ERR_VAR_MISSING;
    }else{
        printf("unrecognized response: %s\n", response);
        exit(EXIT_FAILURE);
    }
}

static void
print_help(char* name)
{
    printf("%s -- Testni odjemalec za deljene spremenljivke.\n", name);
    printf("\n");
    printf("UPORABA\n");
    printf("    %s [-h] [-t timeout] [-d timeout] UKAZ IME\n", name);
    printf("\n");
    printf("UKAZ\n");
    printf("    SET\n");
    printf("        Nastavi vrednost spremenljivke, v njo zapiše vsebino standardnega izhoda (največ 4096 zlogov). Če ne obstaja ustvari novo.\n");
    printf("    UNSET\n");
    printf("        Izbriše spremenljivko.\n");
    printf("    GET\n");
    printf("        Izpiše vrednost spremenljivke na standardni izhod.\n");
    printf("    WAIT\n");
    printf("        Počaka na spremembo spremenljike (SET ali UNSET iz drugega procesa.\n");
    printf("\n");
    printf("IME\n");
    printf("    Ime spremenljivke, katero želimo uporabiti.\n");
    printf("\n");
    printf("ZASTAVICE\n");
    printf("    -h\n");
    printf("        Izpis pomoči z vsemi zastavicami in njihovimi opisi.\n");
    printf("\n");
    printf("    -t timeout\n");
    printf("        Proces se zaključi čez podan čas (v milisekundah) ne glede na uspešnost ukaza. Privzeto čaka neskončno.\n");
    printf("\n");
    printf("    -d timeout\n");
    printf("        Po izvedbi operacije, preden proces zaključi komunikacijo, počaka za izbran čas (v milisekundah). Privzeto zaključi takoj.\n");
    printf("\n");
    printf("IZHODNI STATUS\n");
    printf("    0 - se je uspešno zaključil\n");
    printf("    1 - spremenljivka ne obstaja\n");
    printf("    2 - napaka pri ustvarjanju\n");
    printf("    3 - je bila nastavljena (WAIT dočakal SET)\n");
    printf("    4 - je bila izbrisana (WAIT dočakal UNSET)\n");
    printf("    5 - potekel je čas (-t)\n");
    printf("    128 - napačno podani parametri\n");
    printf("\n");
}

void* thread_timeout_watchdog(void* args){
   int timeout_ms=*(int*)args;
   usleep(timeout_ms*1000);
   printf("timeout triggered\n");
   exit(ERR_TIMEOUT);
}

int
main(int argc, char *argv[])
{
    int opt;
    int delay_ms=0;
    int timeout_ms=0;
    while ((opt = getopt(argc, argv, "ht:d:")) != -1) {
        switch (opt) {
            case 'h':
                print_help(argv[0]);
                exit(EXIT_SUCCESS);
                break;
            case 't': // timeout time
                timeout_ms = atoi(optarg);
                break;
            case 'd': // delay time
                delay_ms = atoi(optarg);
                break;
            default:
                exit(EXIT_FAILURE);
                break;
        }
    }
    if(argc-optind!=2){
       printf("napačno število parametrov (potrebuje ukaz in ime spremenljivke)\n"); 
        print_help(argv[0]);
        exit(ERR_CMD_PARAMS);
    }

    char *command = argv[optind];
    char *var_name = argv[optind+1];

    int (*cmd_fun)(int, char*, int);
    if(strcmp(command, "SET")==0){
        cmd_fun=set_variable;
    }else
    if(strcmp(command, "UNSET")==0){
        cmd_fun=unset_variable;
    }else
    if(strcmp(command, "GET")==0){
        cmd_fun=get_variable;
    }else
    if(strcmp(command, "WAIT")==0){
        cmd_fun=wait_variable;
    }else{
        printf("neprepoznan ukaz: %s\n", command);
        exit(ERR_CMD_PARAMS);
    }

    printf("timeout: %d ms, delay: %d ms\n", timeout_ms, delay_ms);

    if(timeout_ms > 0){
        pthread_t tid=0;
        pthread_create(&tid, 0, thread_timeout_watchdog, (void*)&timeout_ms);
        pthread_detach(tid);
    }


    int connection_fd = create_connection();
    int r = cmd_fun(connection_fd, var_name, delay_ms);
    destroy_connection(connection_fd);

    return r;
}
