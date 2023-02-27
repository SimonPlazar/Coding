
#include "variable_struct.h"
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>

void
init_variable(struct variable_struct* var, const char name[])
{
    printf("variable initialized\n");
    strncpy(var->name, name, MAX_NAME_LEN);
    memset(var->data, 0, 4096);

    var->reading = 0;
    var->waiting = 0;
    pthread_mutex_init(&var->m1, NULL);
    pthread_mutex_init(&var->m2, NULL);

    var->isChanged = false;
    var->isDeleted = false;

    // tukaj inicializirajte struture, ki jih boste potrebovali
    // za posamezno spremenljivko
}

void
clear_variable(struct variable_struct* var)
{
    // tukaj sprostite dinamicno alocirane ali inicializirane spremenljivke
    //
    // preden lahko izbrisete vsebino, morate biti prepricani, da
    // nihce ne pise ali bere spremenljivke
    //
    // tukaj morate tudi opozoriti na spremembo spremenljivke,
    // ce imate implementirano cakanje na spremembe
    // in nato pocakati, da se ti zakljucijo klici

    var->isDeleted = true;

    while (true) {
        if (var->reading == 0 && var->waiting == 0) break; // ce vec noben ne caka ali bere, zbrisemo variable
    }

    printf("variable cleared\n");
    memset(var->name, 0, MAX_NAME_LEN);
    memset(var->data, 0, 4096);

}

void
read_variable_lock(struct variable_struct* var, void (*read_function)(struct variable_struct* var, void* args), void* args)
{
    // tukaj zaklenete dostop do spremenjlivke za branje
    // najboljsa resitev bo omogocila vecim odjemalcem hkrati brati spremenljivko
    // ampak nikomur pisati/brisati
    // ne pozabiti odkleniti dostopa, ko se branje zakljuci

    if (pthread_mutex_lock(&var->m1) != 0) {
        perror("Napaka pri zaklepanju");
        return;
    }

    var->reading++;

    if (var->reading == 1) {
        if (pthread_mutex_lock(&var->m2) != 0) {
            perror("Napaka pri zaklepanju");
        return;
        }
    }

    if (pthread_mutex_unlock(&var->m1) != 0) {
        perror("Napaka pri odklepanju");
        return;
    }

    read_function(var, args); // ta funkcija bo poskrbela za dejansko branje

    var->reading--;
    if (var->reading == 0) {
        if (pthread_mutex_unlock(&var->m2) != 0) {
            perror("Napaka pri zaklepanju");
            return;
        }
    }
}

void
write_variable_lock(struct variable_struct* var, void (*write_function)(struct variable_struct* var, void* args), void* args)
{
    // tukaj zaklenete dostop do spremenjlivke za pisanje
    // ne glede na implementacijo lahko samo en odjemalec hkrati pise v
    // spremenljivko
    // ne pozabiti odkleniti dostopa, ko se pisanje zakljuci

    if (pthread_mutex_lock(&var->m2) != 0) {
        perror("Napaka pri zaklepanju");
        return;
    }

    printf("variable write\n");
    write_function(var, args); // ta funkcija bo poskrbela za dejansko branje
    var->isChanged = true;

    if (pthread_mutex_unlock(&var->m2) != 0) {
        perror("Napaka pri odklepanju");
        return;
    }
}

int
wait_variable_lock(struct variable_struct* var)
{
    // tukaj moramo pocakati, da se spremenljivka spremeni
    // funkcija naj ne vrne dokler nekdo ne pise v spremenljivko
    // ali jo izbrise
    // naj vrne 0 ce je bila spremenljivka pisana
    // naj vrne 1 ce je bo spremenljivka izbrisana
    printf("variable wait for change\n");

    var->isChanged = false;
    var->isDeleted = false;
    var->waiting++;

    while(true) {
        if (var->isChanged) {
            var->waiting--;
            return 0;
        }

        if (var->isDeleted) {
            var->waiting--;
            return 1;
        }
    }

    return 0;
}