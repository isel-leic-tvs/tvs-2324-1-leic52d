.section .text
.global _start

_start:
/* syscall write(int fd, const void *buf, size_t count) */
    mov x0, #1     
    ldr x1, =msg 
    ldr x2, =len 
    mov w8, #64 
    svc #0

/* syscall exit(int status) */
    mov x0, #0 
    mov w8, #93 
    svc #0

msg:
.ascii "Hello, from ARM64!\n"
len = . - msg
