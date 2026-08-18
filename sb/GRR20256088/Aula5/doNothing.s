    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $45, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
