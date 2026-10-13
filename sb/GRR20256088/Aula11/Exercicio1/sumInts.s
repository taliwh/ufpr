
.text
.globl sumInts 
.type sumInts, @function

sumInts:
    pushq %rbp
    movq %rsp, %rbp

    movl %edi, %eax
    addl %esi, %eax

    movq %rbp, %rsp
    popq %rbp
    ret






