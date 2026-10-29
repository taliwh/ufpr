    .equ FRAME, 16

.section .rodata
scanFormat:
    .string "%i" 
printFormat:
    .string "%i\n"

.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $FRAME, %rsp

    movq $scanFormat, %rdi
    leaq -4(%rbp), %rsi
    movq $0, %rax 
    call scanf

    movl $1, %ebx # valor atual
    movl $0, %r12d # valor anterior
    
    # se for 0, nao ha pq fazer loop, acaba o programa
    cmpl $0, -4(%rbp)
    je fim

while:
    # verifica se o valor atual e maior que o valor digitado
    cmpl -4(%rbp), %ebx
    ja fim

    movq $printFormat, %rdi
    movl %ebx, %esi
    movq $0, %rax
    call printf                  

    # usa um registrador auxiliar (eax) pra reservar o atual
    movl %ebx, %eax
    
    # calcula o novo valor atual
    addl %r12d, %ebx

    # atualiza o valor anterior (agr e 1 valor antes do atual)
    movl %eax, %r12d

    jmp while

fim:
    movq %rbp, %rsp
    popq %rbp
    ret
