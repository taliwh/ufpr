#constante
    .equ STDIN, 0
    .equ STDOUT, 1
    .equ line, -16
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
    leaq vetor(%rbp), %rsi     # -(%rsi)(%rbp) testar dps
    movl $16, %edx
    call read

    leaq vetor(%rbp), %rcx # ponteiro do comeco da pilha

// faz o echo nrmal
while:
    cmpb $0, (%rcx) # ve se eh 
    je fim
    movb (%rcx), %al
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