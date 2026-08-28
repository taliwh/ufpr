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

    movl %STDIN, %edi
    leaq vetor(%rbp), %rsi  
    movl $16, %edx
    call read
    movq %rax, -24(%rbp) //preciso disso so pro write ?
    movq -24(rbp), %rdx
    
while:
    cmpb $0, (%rdx) # ve se eh /0
    je fim
    movb 
    movb , %al
    movb %al, %cx # resultado na pilha
    leaq 1(%rcx), %rcx # inc(?)

fim:
    movl %STDOUT, %edi
    leaq vetor (%rbp), %rsi # achoq  nem precisa
    movl $16, %edx
    call write

        movl $0, %eax 
        movq %rbp, %rsp
        popq %rbp 
        ret 