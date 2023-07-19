#ifndef __MISC_H__
#define __MISC_H__

// Ce je result == -1, izpisi napako in koncaj proces
void check_ptrace(long result);

// Ce je result == -1, izpisi napako in koncaj proces
void check_execve(int result);

// 
void check_waitpid_status(int wstatus);

#endif // __MISC_H__
