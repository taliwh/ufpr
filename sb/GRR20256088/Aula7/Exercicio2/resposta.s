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
    # VERIFICACAO COM IF PRA CONTROLAR OQ O USUARIO VAI DIGITAR
    # TESTAR O CODIGO COM WRITE E READ PRA VER COMO Q EH

while:
    cmpb $0, (%rsi)
    je write

    # pega oq ta apontado pelo rsi na pilha e move pro reg al
    movb (%rsi), %al

    # se o valor lido eh menor que o ascii do a
    cmpb $'a', %al
    jb fim

    # se o valor lido eh maior que o ascii do z
    cmpb $'z', %al
    ja fim

    subb $caps, %al
    movb %al, (%rsi)

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
