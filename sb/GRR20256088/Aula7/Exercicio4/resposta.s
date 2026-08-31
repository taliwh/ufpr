    .equ FRAME, 16

.section .rodata
scanFormat:
    .string "%i" 
printFormat:
    .string "%i\n"

.text
.globl main
.type main, @function

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $FRAME, %rsp

    movq $scanFormat, %rdi
    leaq -4(%rbp), %rsi
    movq $0, %rax 
    call scanf

    # pega o inteiro lido e coloca em edx
    # movl -4(%rbp), %edx

    movl $0, %r12d # 1 termo fibo (termo ant)
    movl $1, %ebx # 2 termo fibo (termo atual)

    movq $printFormat, %rdi
    movl $0, %esi
    movq $0, %rax
    call printf

    # se edx for 0, nao ha pq fazer loop, acaba o programa
    cmpl $0, -4(%rbp)
    je fim

while:
    # verifica se o valor atual e maior que o valor digitado
    cmpl -4(%rbp), %ebx
    ja fim

    movq $printFormat, %rdi
    movl %ebx, %esi
    movq $0, %rax
    call printf                  

    # usa um registrador auxiliar (eax) pra reservar o atual
    movl %ebx, %eax
    
    # calcula o novo valor atual
    addl %r12d, %ebx

    # atualiza o valor anterior (agr e 1 valor antes do atual)
    movl %eax, %r12d

    jmp while

fim:
    movq %rbp, %rsp
    popq %rbp
    ret









/*\
veriricar se o valor nao eh numero dps
valor atual = 3
valor anterior 2
0   1     1      2     3
          ant   atual  novo 

val_atual = 1
val_ANTERIOR = 0
enquanto valor atual <= valor digitado faca
    c
    addq valoranterior, valor atual



val atual = 3
val anterior = 1


val_atual = val_ant + val_atual
addl val_ant, val_atual

val_ant = val_atual - val_ant
movl val_atual, aux 
subl val_ant, aux
movl aux, val_ant

# nao pode pq vai sobrescrever o val atual, e precisamos dele para atualizar o proximo val atual
subl valant, val atual 

# sub normal nao funciona  pois vai fazer na ordem errada
val_ant = val_ant - val_atual
subl val_atual, val_ant





*/