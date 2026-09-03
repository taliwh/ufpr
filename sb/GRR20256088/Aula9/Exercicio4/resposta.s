
    .equ VET_SIZE12, 256
    .equ VET_SIZE3, 512
    .equ FRAME, 16
.section .rodata
printFormat:
    .string "%i "
.section .bss
    .lcomm VET_1 VET_SIZE12
    .lcomm VET_2 VET_SIZE12
    .lcomm VET_3 VET_SIZE3

.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp

    movq $VET_1, %rax
    leaq VET_SIZE12(%rax), %rcx  # fim do 1 vetor
loop1:
    cmpq %rcx, %rax
    je fim_loop1

    movl $1, (%rax)
    addq $4, %rax

    jmp loop1
fim_loop1:
    movq $VET_2, %rax
    movq $VET_2, %rcx
    addq $VET_SIZE12, %rcx
loop2:
    cmpq %rcx, %rax
    je fim_loop2

    movl $2, (%rax)
    addq $4, %rax

    jmp loop2
fim_loop2:
    movq $VET_1, %rax
    movq $VET_2, %rcx 
    movq $VET_3, %rdx
    leaq VET_SIZE3(%rdx), %rbx # fim do 3 vetor
loop3:
    cmpq %rbx, %rdx
    ja fim_loop3

    movl (%rax), %r12d
    movl %r12d, (%rdx)
    movl (%rcx), %r12d
    movl %r12d, 4(%rdx)

    addq $4, %rax
    addq $4, %rcx
    addq $8, %rdx

    jmp loop3
fim_loop3:
    movq $VET_3, %r14
    leaq VET_SIZE3(%r14), %r15 # fim do 3 vetor
write:
    cmpq %r15, %r14
    ja fim
    movq $printFormat, %rdi
    movl (%r14), %esi
    movq $0, %rax
    call printf

    addq $4, %r14
    jmp write
fim:
    movl $0, %eax
    movq %rsp, %rbp
    popq %rbp
    ret
