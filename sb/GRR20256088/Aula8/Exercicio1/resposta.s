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
    leaq VETOR(%rip), %rcx
    leaq VETOR(%rip), %rcx
    movl $127, %eax
loop_ascii:
    movl $127, %edx
    subl %eax, %edx  # edx vale 0, dps 1, dps 2, dps 3, ...
    movb %dl, (%rcx)
    incq %rcx
    subl $1, %eax
    jnz loop_ascii # loop (se eax n for zero)

    movq $VETOR, %r12    # inicio do vetor
    leaq 127(%r12), %r13 # final do vetor

loop_impressao:
    movq $printFormat, %rdi # endereço da string em rdi
    movsbl (%r12), %esi
    movsbl (%r12), %edx
    movq $0, %rax # sem ponto flutuante
    call printf
    incq %r12
    cmpq %r13, %r12
    jne loop_impressao

fim:
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
    