
.text
.globl fibo
.type fibo, @function

fibo:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $0, %ecx # primeiro termo
    movl $1, %eax # segundo termo

    cmpl $0, %edi
    je nenhum

    cmpl $1, %edi
    je primeiro

    cmpl $2, %edi
    je segundo

    subl $2, %edi # ajusta edi pra posicao ficar certinha

loop: 
    cmpl $0, %edi
    je fim

    movl %eax, -4(%rbp)
    addl %ecx, %eax
    movl -4(%rbp), %ecx
    decl %edi

    jmp loop

fim:
    movq %rbp, %rsp 
    popq %rbp
    ret
nenhum:
    movl $-1, %eax
    jmp fim
primeiro:
    movl $0, %eax
    jmp fim
segundo:
    movl $1, %eax
    jmp fim

/*
ant = 0
atual = 1

enquanto i != n faca
    aux = atual
    atual = ant + atual
    ant = aux
    i++
*/