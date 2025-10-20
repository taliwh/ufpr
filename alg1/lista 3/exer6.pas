(* Faça um programa Pascal que leia um número inteiro positivo N do teclado. Depois disso, o programa deve calcular e imprimir todos os arranjos de dois números inteiros positivos A, B, ambos menores que N, de forma que quando somados (A + B), resultam no número N. Cada arranjo A, B deve ser impresso em uma linha de saída.

Exemplos:
Entrada 1:
7

Saida Esperada 1:
1 6
2 5
3 4
4 3
5 2
6 1 *)

program soma;
var
    i, j, tam: longint;
begin
    read(tam);
    i:= 1;
    j:= tam - 1;
    while ((i <= tam - 1) and (j >= 1)) do
    begin
        if (i + j = tam) then
            writeln(i, ' ', j);
        i:= i + 1;
        j:= j - 1;
    end;
end.
