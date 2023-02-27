#ifndef VARIABLE_LIST_STRUCT_H_
#define VARIABLE_LIST_STRUCT_H_

#include "definitions.h"
#include "variable_struct.h"

struct variables_list_struct{
    pthread_mutex_t lock;
    struct variable_struct variables_array[MAX_VAR_COUNT];
};

void
init_variables_list(struct variables_list_struct* var_list_obj);

void
clear_variables_list(struct variables_list_struct* var_list_obj);

struct variable_struct*
find_named_variable(struct variables_list_struct *var_array_obj, const char var_name[]);

struct variable_struct*
create_new_variable(struct variables_list_struct *var_array_obj, const char var_name[]);

int
remove_named_variable(struct variables_list_struct *var_array_obj, const char var_name[]);

#endif
