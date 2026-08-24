# com rbp:
        .text
        .globl main
        .type main, @function
main:
        pushq %rbp # salvar o frame pointer na pilha
        movq %rsp, %rbp # copiar o stack pointer para o frame pointer
        subq $16, %rsp # Abre 16 bytes de espaço na pilha
        movl $1, -4(%rbp)
        movl $0, -8(%rbp)
        movl $0, %eax # o valor retornado deve estar em EAX (return 0)
        movq %rbp, %rsp # voltar a pilha para a posição original
        popq %rbp # carregar o valor salvo do frame pointer da pilha
        ret

# sem rbp:
        .text
        .globl main
        .type main, @function
main:
        subq $16, %rsp
        movl $1, 12(%rsp)
        movl $0, 8(%rsp)
        movl $0, %eax
        addq $16, %rsp
        ret