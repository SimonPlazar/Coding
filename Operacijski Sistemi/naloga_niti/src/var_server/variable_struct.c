#include "variable_struct.h"
#include <string.h>
#include <stdio.h>

void 
init_variable(struct variable_struct* var, const char name[])
{
    printf("variable initialized\n");
    strncpy(var->name, name, MAX_NAME_LEN);
    memset(var->data, 0, 4096);

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
    
    printf("variable read\n");
    read_function(var, args); // ta funkcija bo poskrbela za dejansko branje
}

void
write_variable_lock(struct variable_struct* var, void (*write_function)(struct variable_struct* var, void* args), void* args)
{
    // tukaj zaklenete dostop do spremenjlivke za pisanje
    // ne glede na implementacijo lahko samo en odjemalec hkrati pise v 
    // spremenljivko
    // ne pozabiti odkleniti dostopa, ko se pisanje zakljuci
    
    printf("variable write\n");
    write_function(var, args); // ta funkcija bo poskrbela za dejansko branje
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
    return 0;    
}
