.section .rodata
scanformat:
    .string "%i"
printformat:
    .string "%i "
printformat2:
    .string "\nquantidade de elementos copiados: %i\n"

.section .bss
    .lcomm vet1 256
    .lcomm vet2 256

.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp

    movq $vet1, %r12 # comeco do vetor 1
    leaq 256(%r12), %r13 # final do vetor 1

ler:
    cmpq %r13, %r12
    je fim_ler

    movq $scanformat, %rdi
    movq %r12, %rsi
    movq $0, %rax
    call scanf

    addq $4, %r12
    jmp ler

fim_ler:
    movq $vet1, %r12 # comeco do vetor 1
    movq $vet2, %r14 # comeco do vetor 2 ( com valores positivos )
    movl $0, %ebx

copia:
    cmpq %r13, %r12
    je fim_copia

    cmpl $0, (%r12) # se o valor for negativo, nao coloca ele dentro do vetor
    jl pular

    movl (%r12), %ecx
    movl %ecx, (%r14)
    addq $4, %r14

    incl %ebx # contador de valores positivos

pular:
    addq $4, %r12
    jmp copia

fim_copia:
    movq $vet2, %r14 # comeco do vetor 2
    movl %ebx, %r12d

printar:
    cmpl $0, %ebx
    je fim

    movq $printformat, %rdi
    movl (%r14), %esi
    movq $0, %rax
    call printf

    addq $4, %r14
    decl %ebx
    jmp printar

fim:
    movq $printformat2, %rdi
    movl %r12d, %esi
    movq $0, %rax
    call printf

    movq %rbp, %rsp
    popq %rbp
    ret








