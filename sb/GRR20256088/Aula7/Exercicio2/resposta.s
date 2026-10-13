# constantes
    .equ line, -16
    .equ vetor, -16
    .equ caps, 32

.section .rodata
scanFormat:
    .string "%15s"
printFormat:
    .string "%s\n"
.text
.globl main
.type main, @function

                                                                                                                                                
main:
    pushq %rbp
    movq %rsp, %rbp
    addq $line, %rsp

    movq $scanFormat, %rdi # oq lerei
    leaq vetor(%rbp), %rsi # onde
    movq $0, %rax # flag pra ver se ha numero flutuante
    call scanf

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
    movq $printFormat, %rdi
    leaq vetor(%rbp), %rsi
    movq $0, %rax
    call printf

fim:
    movq %rbp, %rsp
    popq %rbp
    ret
