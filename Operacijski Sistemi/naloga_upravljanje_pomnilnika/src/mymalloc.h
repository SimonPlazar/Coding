#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_

#include <stddef.h>

void *mymalloc(size_t size);
void myfree(void *ptr);

#endif // _MYMALLOC_H_
