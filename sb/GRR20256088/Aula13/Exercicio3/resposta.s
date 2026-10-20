.text
.type binario, @function
.globl binario

binario:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl %edi, %eax
    cmpl $0, %edi
    je fim

    movl $2, %ebx
    movq $0, %rdx
    divl %ebx

    movl %edx, -4(%rbp) # guardo o val % 2
    movl $10, -8(%rbp)
    movl %eax, %edi
    call binario
    mull -8(%rbp) # 10 * binario(val/2)
    addl -4(%rbp), %eax

fim:
    movq %rbp, %rsp
    popq %rbp
    ret

/*
int binario (int val) {
    if (val == 0)
        return 0;
    return val % 2 + 10 * binario(val/2);
}
*/