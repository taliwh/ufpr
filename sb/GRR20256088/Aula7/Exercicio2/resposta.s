#constante
    .equ STDIN, 0
    .equ STDOUT, 1
    .equ line, -32
    .equ vetor, -16
    .equ caps, 32
    .text
    .globl main
    .type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    addq $line, %rsp

    movl $STDIN, %edi
    leaq vetor(%rbp), %rsi  
    movl $16, %edx
    call read
    movq %rax, -20(%rbp) 
    movq -16(%rbp), %rdx
    
while:
    cmpb $0, (%rdx) # ve se eh /0
    je fim
    
    # imprime 
    movl $STDOUT, %edi
    movq %rdx, %rsi
    movl $1, %edx 
    call write

    incq %rdx
fim:

    movq %rsp, %rbp
    popq %rbp
    ret

