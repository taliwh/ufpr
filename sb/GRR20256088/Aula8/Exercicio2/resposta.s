    .equ VET_SIZE, 256
.section .rodata
printFormat:
    .string "%i "
.section .bss
    .lcomm VET_1 VET_SIZE
    .lcomm VET_2 VET_SIZE

.text
.globl main
.type main, @function
 # FAZER LOOP NO PRINT
main:   
    pushq %rbp
    movq %rsp, %rbp
    subq $VET_SIZE, %rsp
    movl $0, %edx
    movq $VET_1, %rax
    movq $VET_1, %rcx # final do vetor
    addq $VET_SIZE, %rcx
loop1:
    cmpq %rcx, %rax
    je fim_loop1
    movl %edx, (%rax)
    addq $4, %rax # incrementa o ponteiro
    addl $2, %edx
    jmp loop1
fim_loop1:
    movl $1, %edx
    movq $VET_2, %rax
    movq $VET_2, %rcx
    addq $VET_SIZE, %rcx
loop2:
    cmpq %rcx, %rax
    je fim_loop2
    movl %edx, (%rax)
    addq $4, %rax # incrementa o ponteiro
    addl $2, %edx
    jmp loop2
fim_loop2:
    leaq -VET_SIZE(%rbp), %rbx
    movq $VET_1, %rcx
    movq $VET_2, %rax
somar:
    cmpq %rbx, %rbp
    je fim
    movl (%rcx), %edx
    addl (%rax), %edx
    movl %edx, (%rbx) 
    addq $4, %rbx 
    addq $4, %rcx
    addq $4, %rax
printar:
    movq $printFormat, %rdi
    movq -VET_SIZE(%rbp), %rsi
    movq $0, %rax
    call printf
fim:
    movq %rbp, %rsp
    popq %rbp
    ret








    
