.global _start

.text
_start:
    # write(1, msg, len)
    mov $1,   %rax
    mov $1,   %rdi
    mov $msg, %rsi
    mov $len, %rdx
    syscall

    # exit(0)
    mov $60,  %rax
    mov $0,   %rdi
    syscall

.data
msg:
    .ascii "Hello, world!\n"
    .set    len, . - msg
