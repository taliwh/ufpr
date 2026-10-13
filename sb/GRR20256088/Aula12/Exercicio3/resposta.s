.text
.type digito, @function
.globl digito

int digito(int n, int k) {
    
    if (n == k)
        return 1 + digito(n/10, k);
    return digito(n/10);
}
2
10202


digito:
    pushq %rbp
    movq %rsp, %rbp

    cmpl $0, %edi
    jne continua
    movl $0, %eax
    jmp fim

continua:
    movl %edi, %eax # dividendo
    movl $0, %edx # zera a parte alta do dividendo
    movl $10, %ecx # divisor
    divl %ecx # n mod 10 -> edx
    cmpl %edx, %esi # n % 10 (edx) == k
    jne rec2

rec1: # se for igual
    movl %eax, %edi
    call digito # digito(k, n/10)
    addl $1, %eax
    jmp fim

rec2: # se nao for igual
    movl %eax, %edi
    call digito
    jmp fim
fim:
    movq %rbp, %rsp
    popq %rbp
    ret


