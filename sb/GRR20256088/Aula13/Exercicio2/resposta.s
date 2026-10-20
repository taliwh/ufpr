.text
.type soma, @function
.globl soma


soma:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl %edi, %eax

    movl $10, %ebx
    movq $0, %rdx
    divl %ebx

    movl %edx, -4(%rbp)

    cmpl $0, %eax   
    je guarda

    movl %eax, %edi # coloca n/10 como parametro
    call soma  
    addl -4(%rbp), %eax 
    jmp fim

guarda:
    movl -4(%rbp), %eax 

fim:
    movq %rbp, %rsp
    popq %rbp
    ret