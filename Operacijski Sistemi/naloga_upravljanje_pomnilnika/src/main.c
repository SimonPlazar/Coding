// MAP_ANONYMOUS
#define _GNU_SOURCE

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "mymalloc.h"

void
fill_buffer(void *buffer, size_t size)
{
    // Fill with numbers from 0 to 255
    for (size_t i = 0; i < size; i++) {
        ((unsigned char *)buffer)[i] = i % 256;
    }
}

bool
check_buffer(void *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        if (((unsigned char *)buffer)[i] != i % 256) {
            return false;
        }
    }

    return true;
}

//==============================================================================
// Test 1
//==============================================================================

bool
test_single(size_t size)
{
    void *ptr = mymalloc(size);
    fill_buffer(ptr, size);
    bool ret = check_buffer(ptr, size);
    myfree(ptr);

    return ret;
}

//==============================================================================
// Test 2
//==============================================================================

bool
test_multiple_sequential(size_t size, int times)
{
    bool ret = true;

    for (int i=0; i<times; i++) {
        void *ptr = mymalloc(size);
        fill_buffer(ptr, size);
        ret = ret && check_buffer(ptr, size);
        myfree(ptr);
    }

    return ret;
}

//==============================================================================
// Test 3
//==============================================================================

bool
test_multiple_parallel(size_t size, int times)
{
    bool ret = true;
    void *ptrs[times];

    for (int i=0; i<times; i++) {
        ptrs[i] = mymalloc(size);
        fill_buffer(ptrs[i], size);
    }

    for (int i=0; i<times; i++) {
        ret = ret && check_buffer(ptrs[i], size);
        myfree(ptrs[i]);
    }

    return ret;
}

//==============================================================================
// Test 4
//==============================================================================

bool
test_multiple_parallel_reversed(size_t size, int times)
{
    bool ret = true;
    void *ptrs[times];

    for (int i=0; i<times; i++) {
        ptrs[i] = mymalloc(size);
        fill_buffer(ptrs[i], size);
    }

    for (int i=times - 1; i>=0; i--) {
        ret = ret && check_buffer(ptrs[i], size);
        myfree(ptrs[i]);
    }

    return ret;
}

//==============================================================================
// Test 5
//==============================================================================

bool
test_multiple_parallel_random(size_t size)
{
    bool ret = true;
    void *ptrs[3];

    for (int i=0; i<3; i++) {
        ptrs[i] = mymalloc(size);
        fill_buffer(ptrs[i], size);
    }

    ret = ret && check_buffer(ptrs[1], size);
    myfree(ptrs[1]);

    ret = ret && check_buffer(ptrs[2], size);
    myfree(ptrs[2]);

    ret = ret && check_buffer(ptrs[0], size);
    myfree(ptrs[0]);

    return ret;
}

//==============================================================================
// Test 6
//==============================================================================

bool
test_multiple_3x_sequential()
{
    bool ret = true;
    
    ret = ret && test_multiple_sequential(10, 3);
    ret = ret && test_multiple_sequential(1024, 3);
    ret = ret && test_multiple_sequential(4 * 1024, 3);
    ret = ret && test_multiple_sequential(1024 * 1024, 3);

    return ret;
}

bool
test_multiple_3x_parallel()
{
    bool ret = true;

    ret = ret && test_multiple_parallel(10, 3);
    ret = ret && test_multiple_parallel(1024, 3);
    ret = ret && test_multiple_parallel(4 * 1024, 3);
    ret = ret && test_multiple_parallel(1024 * 1024, 3);

    return ret;
}

bool
test_multiple_3x_parallel_reversed()
{
    bool ret = true;

    ret = ret && test_multiple_parallel_reversed(10, 3);
    ret = ret && test_multiple_parallel_reversed(1024, 3);
    ret = ret && test_multiple_parallel_reversed(4 * 1024, 3);
    ret = ret && test_multiple_parallel_reversed(1024 * 1024, 3);

    return ret;
}

bool
test_multiple_3x_parallel_random()
{
    bool ret = true;

    ret = ret && test_multiple_parallel_random(10);
    ret = ret && test_multiple_parallel_random(1024);
    ret = ret && test_multiple_parallel_random(4 * 1024);
    ret = ret && test_multiple_parallel_random(1024 * 1024);

    return ret;
}

//==============================================================================
// Test 7
//==============================================================================

bool
test_error(size_t size)
{
    void *ptr = mymalloc(size);
    if (ptr == NULL) {
        return true;
    }

    return false;
}

bool
test_error_free()
{
    myfree(NULL);

    return true;
}

//==============================================================================
// Test 8
//==============================================================================

void
run_mem_alloc_prof(char *prof_file_path)
{
    // Open /dev/null
    int devnull = open("/dev/null", O_WRONLY);
    if (devnull == -1) {
        perror("error opening /dev/null");
    }

    // Duplicate stdout
    int stdout_dup = dup(1);
    if (stdout_dup == -1) {
        perror("error duplicating stdout");
    }

    // Duplicate stderr
    int stderr_dup = dup(2);
    if (stderr_dup == -1) {
        perror("error duplicating stderr");
    }

    // Redirect stdout to /dev/null
    if (dup2(devnull, 1) == -1) {
        perror("error redirecting stdout to /dev/null");
    }

    // Redirect stderr to /dev/null
    if (dup2(devnull, 2) == -1) {
        perror("error redirecting stderr to /dev/null");
    }

    close(devnull);

    // Read total program size in pages
    // Size of pid is limited, so this should be more than fine
    char statm_path[100];
    sprintf(statm_path, "/proc/%d/statm", getpid());
    FILE *statm_file = fopen(statm_path, "r");
    int total_size = 0;
    int ret = fscanf(statm_file, "%d", &total_size);
    if (ret != 1) {
        perror("error scanning total program size");
        exit(EXIT_FAILURE);
    }
    fclose(statm_file);
    // dprintf(stdout_dup, "Začetno število strani: %d\n", total_size);

    FILE *prof_file = fopen(prof_file_path, "r");
    if (prof_file == NULL) { 
        perror("error opening file with memory allocation profile");
        exit(EXIT_FAILURE);
    }
    
    char cmd[6] = { 0 };
    char *ret_ptr = fgets(cmd, 5, prof_file);
    if (ret_ptr != cmd) {
        perror("error reading command");
        exit(EXIT_FAILURE);
    }
    
    int n_cmd = 0;
    if (strcmp(cmd, "NDAT") == 0) {
        ret = fscanf(prof_file, " %d ", &n_cmd);
        if (ret != 1) {
            perror("error scanning number of commands");
            exit(EXIT_FAILURE);
        }
    } else {
        dprintf(stderr_dup, "error: NDAT command not found in first line of memory allocation profile");
        exit(EXIT_FAILURE);
    }

    void *data_pts[n_cmd];
    int max_size = total_size;
    int prev_size = total_size;
    
    while (true) {        
        int idx;
        int size;
        
        if (fgets(cmd, 5, prof_file) == 0) {
            break;
        }
        
        if (strcmp(cmd, "ALLO") == 0) {
            if (fscanf(prof_file, " %d %d ", &idx, &size) != 2) {
                perror("error reading ALLO params");
                exit(EXIT_FAILURE);
            }
            data_pts[idx] = mymalloc(size);
            memset(data_pts[idx], 0, size);
            dprintf(stdout_dup, "mymalloc(%d)[%d] - ", size, idx);
        } else if(strcmp(cmd, "FREE") == 0) {
            if (fscanf(prof_file, " %d ", &idx) != 1) {
                perror("error reading FREE params");
                exit(EXIT_FAILURE);
            }
            myfree(data_pts[idx]);
            dprintf(stdout_dup, "myfree()[%d] - ", idx);
        } else {
            dprintf(stderr_dup, "error: no valid command read: %s\n", cmd);
            break;
        }

        statm_file = fopen(statm_path, "r");
        ret = fscanf(statm_file, "%d", &total_size);
        if (ret != 1) {
            perror("error scanning total program size");
            exit(EXIT_FAILURE);
        }
        fclose(statm_file);
        int change_size = total_size - prev_size;
        if (change_size > 0) {
            dprintf(stdout_dup, "razlika alociranih strani: +%d\n", change_size);
        } else {
            dprintf(stdout_dup, "razlika alociranih strani: %d\n", change_size);
        }
        if (total_size > max_size) {
            max_size = total_size;
        }
        prev_size = total_size;
    }

    fclose(prof_file);
    
    // dprintf(stdout_dup, "Maksimalno število strani: %d\n", max_size);
}

//==============================================================================
// Main
//==============================================================================

int
main(int argc, char **argv)
{
    if (argc < 2) {
        printf("ERROR: Specify test name.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "run_mem_alloc_prof") == 0 && argc < 3) {
        printf("ERROR: Specify path to memory allocation profile.\n");
        return EXIT_FAILURE;
    }

    // BEGIN_STRACE
    mmap(NULL, 0, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    bool test_res = false;

    if      (strcmp(argv[1], "test_10B") == 0) test_res = test_single(10);
    else if (strcmp(argv[1], "test_1kB") == 0) test_res = test_single(1024);
    else if (strcmp(argv[1], "test_4kB") == 0) test_res = test_single(4 * 1024);
    else if (strcmp(argv[1], "test_1MB") == 0) test_res = test_single(1024 * 1024);

    else if (strcmp(argv[1], "test_3x10B_sequential") == 0) test_res = test_multiple_sequential(10, 3);
    else if (strcmp(argv[1], "test_3x1kB_sequential") == 0) test_res = test_multiple_sequential(1024, 3);
    else if (strcmp(argv[1], "test_3x4kB_sequential") == 0) test_res = test_multiple_sequential(4 * 1024, 3);
    else if (strcmp(argv[1], "test_3x1MB_sequential") == 0) test_res = test_multiple_sequential(1024 * 1024, 3);
    
    else if (strcmp(argv[1], "test_3x10B_parallel") == 0) test_res = test_multiple_parallel(10, 3);
    else if (strcmp(argv[1], "test_3x1kB_parallel") == 0) test_res = test_multiple_parallel(1024, 3);
    else if (strcmp(argv[1], "test_3x4kB_parallel") == 0) test_res = test_multiple_parallel(4 * 1024, 3);
    else if (strcmp(argv[1], "test_3x1MB_parallel") == 0) test_res = test_multiple_parallel(1024 * 1024, 3);
    
    else if (strcmp(argv[1], "test_3x10B_parallel_reversed") == 0) test_res = test_multiple_parallel_reversed(10, 3);
    else if (strcmp(argv[1], "test_3x1kB_parallel_reversed") == 0) test_res = test_multiple_parallel_reversed(1024, 3);
    else if (strcmp(argv[1], "test_3x4kB_parallel_reversed") == 0) test_res = test_multiple_parallel_reversed(4 * 1024, 3);
    else if (strcmp(argv[1], "test_3x1MB_parallel_reversed") == 0) test_res = test_multiple_parallel_reversed(1024 * 1024, 3);
    
    else if (strcmp(argv[1], "test_3x10B_parallel_random") == 0) test_res = test_multiple_parallel_random(10);
    else if (strcmp(argv[1], "test_3x1kB_parallel_random") == 0) test_res = test_multiple_parallel_random(1024);
    else if (strcmp(argv[1], "test_3x4kB_parallel_random") == 0) test_res = test_multiple_parallel_random(4 * 1024);
    else if (strcmp(argv[1], "test_3x1MB_parallel_random") == 0) test_res = test_multiple_parallel_random(1024 * 1024);

    else if (strcmp(argv[1], "test_multiple_3x_sequential") == 0) test_res = test_multiple_3x_sequential();
    else if (strcmp(argv[1], "test_multiple_3x_parallel") == 0) test_res = test_multiple_3x_parallel();
    else if (strcmp(argv[1], "test_multiple_3x_parallel_reversed") == 0) test_res = test_multiple_3x_parallel_reversed();
    else if (strcmp(argv[1], "test_multiple_3x_parallel_random") == 0) test_res = test_multiple_3x_parallel_random();

    else if (strcmp(argv[1], "test_error_0_B") == 0) test_res = test_error(0);
    else if (strcmp(argv[1], "test_error_1_TB") == 0) test_res = test_error((size_t)1024 * 1024 * 1024 * 1024);
    else if (strcmp(argv[1], "test_error_NULL") == 0) test_res = test_error_free();

    else if (strcmp(argv[1], "run_mem_alloc_prof") == 0) { run_mem_alloc_prof(argv[2]); test_res = true; }
    
    else { printf("ERROR: Invalid test name.\n"); test_res = false; }

    return test_res ? EXIT_SUCCESS : EXIT_FAILURE;
}
