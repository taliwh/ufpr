    .equ FRAME, 16

.section .rodata
scanFormat:
    .string "%i %i %i"
printFormat:
    .string "%i "

.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $FRAME, %rsp

    movq $scanFormat, %rdi
    leaq -12(%rbp), %rsi # a
    leaq -8(%rbp), %rdx # r
    leaq -4(%rbp), %rcx # n
    movq $0, %rax
    call scanf

    movl -12(%rbp), %ebx # primeiro termo da pa
    movl $1, %ecx # iterador do loop

while:
    # se a quantidade de vezes do loop for maior que N (-4(%rbp)), pula pra fora do loop
    cmpl -4(%rbp), %ecx
    ja fim

    movl %ecx, -16(%rbp) # salva o iterador pois o printf destroi ele

    movq $printFormat, %rdi
    movl %ebx, %esi
    movq $0, %rax
    call printf

    movl -16(%rbp), %ecx
    incl %ecx

    # atualizando o termo atual
    addl -8(%rbp), %ebx
    jmp while

fim:
    movq %rbp, %rsp
    popq %rbp
    ret

