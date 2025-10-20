Faça um programa Pascal que leia uma sequência de números inteiros terminada em zero e imprima o maior e o menor número dessa sequência. O valor zero não deve ser ser processado, ele serve para marcar o final da entrada de dados.

Exemplos:
Entrada 1:
1 55 30 -2 560 -1 0

Saída Esperada 1:
560 -2

Entrada 2:
-3 -4 -30 -10 0

Saída Esperada 2:
-3 -30

program data;
var n, a, maior, menor: longint;
begin
    read(n);         //3 2 1
    maior:= n;
    menor:= n;
    while n <> 0 do
begin
    read(n);
    if n = 0 then
    break;
    if n < menor then   
    menor:= n; 
    if n > maior then
    maior:= n;
end;
writeln(maior, ' ', menor);
end.
