
#ifndef VARIABLE_STRUCT_H_
#define VARIABLE_STRUCT_H_

#include "definitions.h"
#include <pthread.h>
#include <stdbool.h>

struct variable_struct{
    char name[MAX_NAME_LEN];
    char data[4096];
    int reading;
    int waiting;
    pthread_mutex_t m1;
    pthread_mutex_t m2;
    bool isChanged;
    bool isDeleted;

    // tukaj dodajte dodatne spremenljivke, ki jih bi potrebovali
    // kljuÄavnice, pogojne spremenljivke, semaforje, ...
};

// v tej funkciji inicializirate vsebino variable_struct (spremenljivke)
void init_variable(struct variable_struct* var, const char name[]);

// v tej funkciji sprostite dinamiÄne strukture, ki ste jih alocirali
void clear_variable(struct variable_struct* var);

// v tej funkciji zaklenete spremenljivko za branje
void read_variable_lock(struct variable_struct* var, void (*read_function)(struct variable_struct*, void*), void* args);
// v tej funkciji zaklenete spremenljivko za pisanje
void write_variable_lock(struct variable_struct* var, void (*write_function)(struct variable_struct*, void*), void* args);
// v tej funkciji poÄakate, da druga nit opozori na spremembo spremenljivke
int wait_variable_lock(struct variable_struct* var);

#endif