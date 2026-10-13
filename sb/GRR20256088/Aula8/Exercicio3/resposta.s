.section .bss
    .lcomm vet_1 256
    .lcomm vet_2 256
    .lcomm vet_3 512

.section .rodata
printformat:
    .string "%i "

.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp

    movq $vet_1, %rcx # comeco do vetor 1
    leaq 256(%rcx), %rdx # final do vetor 1

    movq $vet_2, %rdi # comeco do vetor 2

    movl $0, %esi # valor inicial do vetor 1 de pares
    movl $1, %ebx # valor inicial do vetor 2 de impares
preencher:
    cmpq %rdx, %rcx
    je fim_preencher

    movl %esi, (%rcx)
    movl %ebx, (%rdi)

    addl $2, %esi
    addl $2, %ebx

    addq $4, %rcx
    addq $4, %rdi
    
    jmp preencher

fim_preencher:
    movq $vet_3, %rdx # ptr par
    leaq 4(%rdx), %rbx # ptr impar

    leaq 512(%rdx), %rcx # final do vetor 3

    movq $vet_1, %rsi # comeco do vetor 1
    movq $vet_2, %rdi # comeco do vetor 2

intercala:
    cmpq %rcx, %rdx
    je fim_int

    # pega oq ta no vetor 1 e poe nos indices pares do vetor 3
    movl (%rsi), %eax
    movl %eax, (%rdx)

    # pega oq ta no vetor 2 e poe nos indices impares do vetor 3
    movl (%rdi), %eax
    movl %eax, (%rbx)

    addq $8, %rdx
    addq $8, %rbx

    addq $4, %rsi
    addq $4, %rdi

    jmp intercala

fim_int:
    movq $vet_3, %r12 # comeco do vetor 3
    leaq 512(%r12), %r13 # final do vetor 3    

printar:
    cmpq %r13, %r12
    je fim

    movq $printformat, %rdi
    movl (%r12), %esi
    movq $0, %rax
    call printf
    
    addq $4, %r12
    jmp printar

fim:
    movq %rbp, %rsp
    popq %rbp
    ret