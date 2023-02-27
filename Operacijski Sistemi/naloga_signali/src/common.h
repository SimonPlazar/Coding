#ifndef _COMMON_H
#define _COMMON_H

#include <time.h>

struct job_node
{
    time_t time;
    char cmd[1024];
    struct job_node *next;
};

struct job_node *read_job_list(const char *path);
void free_job_list(struct job_node *job_list);

#endif // _COMMON_H
