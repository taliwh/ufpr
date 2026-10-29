    .equ FRAME, 16
    .equ READ, 0
    .equ STDIN, 0
    .equ WRITE, 1
    .equ STDOUT, 1
    .equ EXIT, 60
.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $FRAME, %rsp

    # aqui ele vai ler os bytes de cada caractere

    movq $STDIN, %rdi # arquivo que vou ler
    leaq -16(%rbp), %rsi # endereco onde vou deixar oq eu li
    movl $12, %edx # bytes maximos q posso ler (vai ate 4 bilhoes)
    movl $READ, %eax
    syscall

    decl %eax
    leaq -16(%rbp), %rdi
    movl %eax, %esi
    call atoi

    movl %eax, -4(%rbp)

    movl $1, %ebx # valor atual
    movl $0, %r12d # valor anterior
    
    # se for 0, nao ha pq fazer loop, acaba o programa
    cmpl $0, -4(%rbp)
    je fim

while:
    # verifica se o valor atual e maior que o valor digitado
    cmpl -4(%rbp), %ebx
    jg fim

    movl %ebx, %edi
    leaq -16(%rbp), %rsi
    call itoa            
    
    movq $STDOUT, %rdi
    leaq -16(%rbp), %rsi
    movl $12, %edx # bytes maximos q posso imprimir (vai ate 4 bilhoes)
    movl $WRITE, %eax
    syscall 
    
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

    movl $0, %edi
    movl $EXIT, %eax
    syscall
