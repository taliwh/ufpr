# ssize_t write(int fd, const void *buf, size_t count)
# o count e passado dentro de edx
# ssize_t read(int fd, void *buf, size_t count)

# constantes
    .equ STDIN, 0
    .equ STDOUT, 1

# posicoes na stack

    .equ vetor, -16                   # .equ: define do c
    .equ local_size, 16

    .text
    .globl main
    .type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $local_size, %rsp         

    movl $STDIN, %edi   
    leaq vetor(%rbp), %rsi     
    movl $2, %edx              
    call read

    movl $STDOUT, %edi
    leaq vetor(%rbp), %rsi
    movl $2, %edx
    call write

    movl $0, %eax  << change the value here
    movq %rbp, %rsp
    popq %rbp
    ret
