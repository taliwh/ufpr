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
    subq $local_size, %rsp           # precisamos de espaco na pilha pro vetor de buffer (16 bytes, tam do local_size)

    movl $2, %edx 
    leaq vetor(%rbp), %rsi           # dentro do rsi vai ter o ponteiro do vetor , eh q pois tem 64 bits na memoria(8 bytes) o vetor nao comeca em -16 (???????????? socor)
    movl $STDIN, %edi                # (nao dava pra usar addi?)
    call read

    movl $2, %edx
    leaq vetor(%rbp), %rsi
    movl $STDOUT, %edi
    call write

    movl $45, %eax
    movq %rbp, %rsp
    popq %rbp
    ret

