# constantes
    .equ line, -16
    .equ vetor, -16
    .equ caps, 32
    .equ READ, 0
    .equ WRITE, 1
    .equ STDIN, 0
    .equ STDOUT, 1

.section .rodata
printFormat:
    .string "%s\n"
.text
.globl main
.type main, @function
              
main:
    pushq %rbp
    movq %rsp, %rbp
    addq $line, %rsp

    movq $STDIN, %rdi # em q arquivo e pra por
    leaq vetor(%rbp), %rsi # onde 
    movq $16, %rdx # quantidade de coisa q vo ler
    movq $READ, %rax # flag pra ver se ha numero flutuante
    syscall

    movq %rax, %r8 # guarda a quantidade de bytes lidos

    leaq vetor(%rbp), %rsi


while:
    cmpb $0, (%rsi)
    je write

    # pega oq ta apontado pelo rsi na pilha e move pro reg al
    movb (%rsi), %al

    # se o valor lido eh menor que o ascii do a
    cmpb $'a', %al
    jb fora

    # se o valor lido eh maior que o ascii do z
    cmpb $'z', %al
    ja fora

    subb $caps, %al
    movb %al, (%rsi)
    
fora:
    incq %rsi
    jmp while

write:
    movq $STDOUT, %rdi
    leaq vetor(%rbp), %rsi
    movq %r8, %rdx
    movq $WRITE, %rax
    syscall

fim:
    movq %rbp, %rsp
    popq %rbp
    ret
