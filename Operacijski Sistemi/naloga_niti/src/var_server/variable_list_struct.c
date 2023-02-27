#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "variable_list_struct.h"

void
init_variables_list(struct variables_list_struct* var_list_obj)
{
    // setup mutex
    int err_no=pthread_mutex_init(&var_list_obj->lock, NULL);
    if(err_no != 0){
        perror("ERROR (init_variable_list, phread_mutex_init)");
        exit(2);
    }
}

void
clear_variables_list(struct variables_list_struct* var_list_obj)
{
    // clear mutex
    pthread_mutex_destroy(&var_list_obj->lock);
}

static struct variable_struct*
__find_named_variable__(struct variables_list_struct *var_list_obj, const char var_name[])
{
    // find a variable of a given name, the list must already be locked
    struct variable_struct *var_obj=NULL;
    for(int i=0; i<MAX_VAR_COUNT; i+=1)
    {
        if(strcmp(var_list_obj->variables_array[i].name, var_name)==0)
        {
            var_obj=&var_list_obj->variables_array[i];
            break;
        }
    }
    return var_obj;
}

struct variable_struct*
find_named_variable(struct variables_list_struct *var_list_obj, const char var_name[])
{
    // prevent others from changing the list and it's entries
    pthread_mutex_lock(&var_list_obj->lock);
    // find a variable of a given name
    struct variable_struct *var_obj = __find_named_variable__(var_list_obj, var_name);
    pthread_mutex_unlock(&var_list_obj->lock);
    return var_obj;
}

struct variable_struct*
create_new_variable(struct variables_list_struct *var_list_obj, const char var_name[])
{
    // prevent others from changing the list and it's entries
    pthread_mutex_lock(&var_list_obj->lock);
    // find an empty variable
    struct variable_struct* var_obj = __find_named_variable__(var_list_obj, "");
    if(var_obj != NULL){
        // init the variable here
        init_variable(var_obj, var_name);
    }
    pthread_mutex_unlock(&var_list_obj->lock);
    return var_obj;
}

int
remove_named_variable(struct variables_list_struct *var_list_obj, const char var_name[])
{
    int ret_val=0;
    // prevent others from changing the list and it's entries
    pthread_mutex_lock(&var_list_obj->lock);
    // find the named variable
    struct variable_struct* var_obj =  __find_named_variable__(var_list_obj, var_name);
    if(var_obj == NULL){
        ret_val=-1;
    } else {
        // if the variable exists, clear it
        clear_variable(var_obj);
    }
    pthread_mutex_unlock(&var_list_obj->lock);
    return ret_val;
}

