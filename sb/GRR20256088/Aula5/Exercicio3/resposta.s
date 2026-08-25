
    .equ STDIN, 0
    .equ STDOUT, 1
    .equ VETORSIZE, 16
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $STDIN, %edi
    leaq -VETORSIZE(%rbp), %rsi  
    movl $2, %edx               
    call read

    movl $STDIN, %edi
    leaq -VETORSIZE+1(%rbp), %rsi # sobrescreve o enter (\n) do primeiro caracter lido em cima
    movl $2, %edx               
    call read

    movb -VETORSIZE(%rbp), %al # pega o primeiro caractere
    movb -VETORSIZE+1(%rbp), %cl # pega o segundo caractere

    subb $48, %al # pega o deciaml doa scci
    subb $48, %cl # pega o decimal do ascii

    addb %al, %cl # soma os dois decimal
    addb $48, %cl # transforma em ascii de nv

    movb %cl, -VETORSIZE(%rbp) # coloca o resultado devolta na pilha
    movb $10, -VETORSIZE+1(%rbp) # coloca o \n depois do resultado

    movl $STDOUT, %edi
    leaq -VETORSIZE(%rbp), %rsi # passa o endereco do resultado
    movl $2, %edx
    call write

    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret


