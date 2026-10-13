    .text
    .type fat, @function 
    .globl fat

fat:
    pushq %rbp
    movq %rsp, %rbp

    movl %edi, %ecx # salva o n

loop:
    cmpl $1, %edi
    je fim

    subl $1, %edi # edi = n - 1
    movl %edi, %eax
    mull %ecx
    movl %eax, %ecx

    jmp loop
    
fim:
    movq %rbp, %rsp
    popq %rbp
    ret


