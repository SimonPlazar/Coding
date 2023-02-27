#include "common.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void job_list_insert_ordered(struct job_node **job_list, time_t time, char cmd[]);

struct job_node *
read_job_list(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("ERROR: Napaka pri odpiranju datoteke.\nfopen");
        exit(EXIT_FAILURE);
    }

    struct job_node *job_list = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = -1;

    while ((nread = getline(&line, &len, file)) != -1) {
        // Trim leading spaces and tabs.
        size_t pos = 0;
        while (isblank(line[pos]) && line[pos] != '\n') {
            pos++;
        }

        // Skip comments and empty lines.
        if (line[pos] == '#' || line[pos] == '\n') {
            continue;
        }

        // Set tm.tm_isdst to correct value.
        time_t raw_time = time(NULL);
        struct tm *tm = localtime(&raw_time);

        char cmd[1024];
        sscanf(line, "%d %d %d %d %d %d %[^\n]s",
               &tm->tm_sec, &tm->tm_min, &tm->tm_hour,
               &tm->tm_mday, &tm->tm_mon, &tm->tm_year,
               cmd);
        tm->tm_mon = tm->tm_mon - 1;
        tm->tm_year = tm->tm_year + 100;

        raw_time = mktime(tm);

        job_list_insert_ordered(&job_list, raw_time, cmd);
    }

    free(line);

    int ret = fclose(file);
    if (ret != 0) {
        perror("ERROR: Napaka pri zapiranju datoteke.\nfclose");
        exit(EXIT_FAILURE);
    }

    return job_list;
}

void
free_job_list(struct job_node *job_list)
{
    struct job_node *job_node = job_list;
    while(job_node != NULL) {
        struct job_node *next = job_node->next;
        free(job_node);
        job_node = next;
    }
}

static void
job_list_insert_ordered(struct job_node **job_list, time_t time, char cmd[])
{
    struct job_node *job_node = malloc(sizeof(struct job_node));
    job_node->time = time;
    strcpy(job_node->cmd, cmd);
    job_node->next = NULL;

    // If linked list is empty or new job has earlier time than the first one.
    if ((*job_list) == NULL || difftime(job_node->time, (*job_list)->time) < 0) {
        job_node->next = *job_list;
        *job_list = job_node;
    } else {
        struct job_node *current = *job_list;
        while(current->next != NULL && difftime(job_node->time, current->next->time) > 0) {
            current = current->next;
        }
        job_node->next = current->next;
        current->next = job_node;
    }
}
