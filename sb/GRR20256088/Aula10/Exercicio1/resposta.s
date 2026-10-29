.text
.globl dividir
.type dividir, @function

dividir:
    pushq %rbp
    movq %rsp, %rbp 

    # rdi rsi rdx

    movq %rdx, %rcx  # guardando o endereco do resto 

    movl %edi, %eax  # coloca dividendo em eax

    cdq # estende o sinal do valor de 32 bits do eax para os 64 bits do dividendo 
    # verificando o bit mais significativo (mais à esquerda) do eax

    kae <--- edx:eax

    kae / esi = eax

    kae mod esi = edx

    idivl %esi      # edx:eax/esi fica no eax

    movl %edx, (%rcx)

    movq %rbp, %rsp
    popq %rbp 
    ret

    movq $vetor, %rsi
