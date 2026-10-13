
.text
.type fib, @function
.globl fib

fib:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl %edi, %eax

    # caso base (if n <= 1)
    cmpl $1, %edi
    jle fim

    decl %edi # n - 1
    movl %edi, -16(%rbp) # n - 1 na pilha
    call fib # retorna fib (n - 1)
    movl %eax, -12(%rbp)

    movl -16(%rbp), %edi # recupera o n - 1
    decl %edi # n - 2
    call fib # retorna fib (n - 2)
    addl -12(%rbp), %eax # fib (n - 1)  + fib (n - 2)

fim:
    movq %rbp, %rsp
    popq %rbp
    ret
