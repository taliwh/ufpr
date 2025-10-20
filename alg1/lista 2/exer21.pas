Faça um programa Pascal que receba um número inteiro positivo N e calcule a soma dos N primeiros números ímpares positivos. Ao final, imprima esta soma.

Exemplos:
Entrada 1:
2

Saída Esperada 1:
4

Entrada 2:
5

Saída Esperada 2:
25

program sim;
var
    tam, num, i, soma, a: longint;
begin
    read(tam);
    i:= 1;
    num:= 1;
    soma:= 0;
    a:= 0;
    while i <= tam do
    begin                            
        num:= 1 + a;
        soma:= soma + num;
        a:= a + 2;
        i:= i + 1;
    end;
    writeln(soma);
end.
