
# rdi ponteiro dos caractere 
# rsi qtd de caracter

.text
.globl atoi
.type atoi, @function

atoi:
    pushq %rbp
    movq %rsp, %rbp

    movq %rdi, %rcx
    decq %rsi       # n - 1
    addq %rsi, %rcx # rcx + n - 1
    subq $48, (%rcx) # (*(rdi + n - 1) - 48)
    movq (%rcx), %rax

    cmpq $1, %rsi
    je fim

    call atoi

    movq $10, %rbx 
    mulq %rbx # 10 * atoi(rdi, n - 1)
    addq %rcx, %rax  # (*(rdi + n - 1) - 48) + 10 * atoi(rdi, n - 1)

fim:
    movq %rbp, %rsp
    popq %rbp
    ret



/* 
int atoi(char *rdi, int n) {
    if (n == 1) {
        return *rdi - 48;
    }
    
    // vai da direita p esquerda
    return (*(rdi + n - 1) - 48) + 10 * atoi(rdi, n - 1);
}
*/