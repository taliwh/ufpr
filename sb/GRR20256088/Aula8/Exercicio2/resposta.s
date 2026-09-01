    .equ VET_3 256

.section .rodata
printFormat:
    .string "%i"

.section .bss
    .lcomm VET_1 256
    .lcomm VET_2 256
.text
.globl main
.type main, @function

main:   
    pushq %rbp
    movq %rsp, %rbp
    subq $VET_3, %rsp

    leaq -VET_3(%rbp), %rcx
    leaq VET_1(%rbp)
    leaq 
loop:





    
