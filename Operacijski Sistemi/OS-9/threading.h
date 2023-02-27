


#ifndef THREADING_H_
#define THREADING_H_

#include <pthread.h>

struct threading_struct {
    // ce potrebujete dolgotrajno stanje za spodnje funkcije
    // dodajte spremenljivke v to strukturo
    int thread_count;
    pthread_t threads[100];
};

// v tej funkciji inicializirate morebitno stanje v threading_struct
void threading_setup(struct threading_struct *threading_obj);
// v tej spremenljivki pozenete novo nit in v njej klicete podano funkcijo
void handle_in_thread(struct threading_struct *threading_obj, void (*handler_function)(void* args), void* args);
// v tej funkciji pobrisete morebitno stanje v threading_struct 
void threading_cleanup(struct threading_struct *threading_obj);

#endif

