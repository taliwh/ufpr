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
    movq $VET_1, %rax # comeco do vetor 1
    leaq VET_SIZE(%rax), %rcx # fim do vetor 1

# vetor par
loop1:
    cmpq %rcx, %rax
    je fim_loop1
    movl %edx, (%rax)
    addq $4, %rax # incrementa o ponteiro de 4 em 4 pois eh int
    addl $2, %edx
    jmp loop1
fim_loop1:
    movl $1, %edx
    movq $VET_2, %rax # comeco do vetor 2
    leaq VET_SIZE(%rax), %rcx # fim do vetor 2

# vetor impar
loop2:
    cmpq %rcx, %rax
    je fim_loop2
    movl %edx, (%rax)
    addq $4, %rax # incrementa o ponteiro
    addl $2, %edx
    jmp loop2
fim_loop2:
    leaq -VET_SIZE(%rbp), %rbx # comeco do vetor 3 na pilha
    movq $VET_1, %rcx
    movq $VET_2, %rax
somar:
    cmpq %rbp, %rbx
    je f_soma

    movl (%rcx), %edx
    addl (%rax), %edx
    movl %edx, (%rbx) 

    addq $4, %rbx 
    addq $4, %rcx
    addq $4, %rax
    jmp somar
f_soma:
    leaq -VET_SIZE(%rbp), %rbx
write:
    cmpq %rbp, %rbx
    je fim

    movq $printFormat, %rdi
    movl (%rbx), %esi
    movq $0, %rax
    call printf

    addq $4, %rbx
    jmp write

fim:
    movq %rbp, %rsp
    popq %rbp
    ret








    
