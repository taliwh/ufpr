#constantes
    .equ STDOUT, 1
.section .rodata
printFormat:
    .string "%i %c\n"
    .section .bss
    .lcomm VETOR 127
.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    movq $VETOR, %rcx
    movl $127, %eax
loop_ascii:
    movl $127, %edx
    subl %eax, %edx
    movb %dl, (%rcx)
    incq %rcx
    subl $1, %eax
    jnz loop_ascii

    movq $VETOR, %r12
    leaq 127(%r12), %r13

loop_impressao:
    movq $printFormat, %rdi # endereço da string em rdi
    movq $0, %rax # sem ponto flutuante
    movsbl (%r12), %esi
    movsbl (%r12), %edx
    call printf
    incq %r12
    cmpq %r13, %r12
    jne loop_impressao
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
    