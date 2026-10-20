    .section .rodata
    printformat:
        .string "%d) GNU is not Unix, address: %p\n"

    .text
    .type acronimo, @function
    .globl acronimo


acronimo:
    pushq %rbp
    movq %rsp, %rbp

    incl %edi # aumenta o contador da chamada da funcao
    movl %edi, %ebx # guarda o contador no rbx q eh seguro

    movq $printformat, %rdi
    movl %ebx, %esi
    movq %rsp, %rdx
    movq $0, %rax
    call printf

    movl %ebx, %edi # recupera o parametro do contador
    call acronimo


