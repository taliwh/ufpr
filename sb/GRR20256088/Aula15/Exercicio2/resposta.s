/*
int itoa(int n, char *c) {
    if (n < 0) {
        *c = '-';
        return 1 + itoa(-n, c + 1); 
    }
    
    if (n % 10 == n) {
        *c = n + 48;       
        *(c + 1) = 0;    
        return 1;       
    }

    int gravados = itoa(n / 10, c);

    *(c + gravados) = (n % 10) + 48; 
    *(c + gravados + 1) = 0;     

    return gravados + 1;
}

rdi inteiro
rsi ponteiro pro vetor de caracteres
*/

.text
.globl itoa
.type itoa, @function

itoa:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movslq %edi, %rdi # tranforma o int de 32 em 64 bits com a parte alta zerada
if1:
    cmpq $0, %rdi
    jge fim1 # se n for maior ou igual que 0 nao faz o primeiro if

    movb $45, (%rsi) #   *c = '-';

    # ajuste dos parametros (-n, c + 1)
    negq %rdi # - n
    incq %rsi

    call itoa

    incq %rax
    jmp fim

fim1:
    movq $0, %rdx # zera a parte alta
    movq %rdi, %rax # dividendo = n
    movq $10, %rcx # divisor = 10
    divq %rcx # n /10

if2:
    cmpq %rdx, %rdi # n % 10 == n
    jne fim2
    addq $48, %rdi # n + 48
    movb %dil, (%rsi)
    incq %rsi
    movb $0, (%rsi)
    movq $1, %rax
    jmp fim
    
fim2:
    movq %rax, %rdi # coloca n/10 como parametro

    movq %rsi, -16(%rbp) # guarda o valor do rsi
    movq %rdx, -8(%rbp) # guarda valor do resto

    call itoa

    movq -16(%rbp), %rsi
    movq -8(%rbp), %rdx

    addq %rax, %rsi #  *(c + gravados)
    addq $48, %rdx # (n % 10) + 48; 
    movb %dl, (%rsi) # *(c + gravados) = (n % 10) + 48; 

    incq %rsi #  *(c + gravados + 1)
    movb $0, (%rsi) # *(c + gravados + 1) = 0;     

    incq %rax

fim:
    movq %rbp, %rsp
    popq %rbp
    ret

