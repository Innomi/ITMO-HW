    .section .text
    .global _start
_start:
    mov $1, %rdi
    mov $1, %rax
    mov $hello, %rsi
    mov $SZ, %rdx
call:
    syscall
    sub %rax, %rdx
    add %rax, %rsi
    mov $1, %rax
    cmp $0, %rdx
    jne call

    xchg %rax, %rbx
    xor %rbx, %rbx
    int $0x80

hello:  .ascii "Hello, world!\n"
        SZ = . - hello