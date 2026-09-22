.text
.globl fibo
.type fibo, @function

fibo:
    pushq %rbp
    movq %rsp, %rbp
    subq $FRAME, %rsp

    movl $0, -4(%rbp) # primeiro termo
    movl $1, -8(%rbp) # segundo termo

5) como entender um binario crackeado refletir xd