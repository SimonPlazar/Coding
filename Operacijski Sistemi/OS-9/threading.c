


#include "threading.h"
#include <stdio.h>
#include <pthread.h>


void
threading_setup(struct threading_struct *threading_obj)
{
    // tukaj pripravite nitenje
    // inicializirajte morebitne spremenljivke v podan threading_struct
    printf("threading setup\n");
    threading_obj->thread_count = 0;
}

void
handle_in_thread(struct threading_struct *threading_obj, void (*handler_function)(void* args), void* args)
{
    printf("start new thread\n");
    pthread_t t;
    int status;
    status = pthread_create(&t, NULL, (void*)(handler_function), args);
    if (status != 0) {
        perror("napaka pri ustvarjanju niti.");
    } else {
        threading_obj->threads[threading_obj->thread_count] = t;
        threading_obj->thread_count++;
    }
}

void
threading_cleanup(struct threading_struct *threading_obj)
{
    printf("threading cleanup\n");
    for(int i=0; i<threading_obj->thread_count; i++) {
        pthread_join(threading_obj->threads[i], NULL);
    }
}

