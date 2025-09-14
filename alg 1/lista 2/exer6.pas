Faça um programa Pascal que leia do teclado três valores inteiros representando a data de nascimento de uma pessoa (dia, mês e ano) e imprima quantos anos completos ela terá no dia 29/04/2021.

Exemplos:

Entrada 1:
17 05 1988

Saída Esperada 1:
32

Entrada 2:
29 04 2021

Saída Esperada 2:
0

program data;
var dia, mes, ano, idade, somademeses: integer;
begin
read(dia, mes, ano);
somademeses:= (15 - mes);
if (mes <= 4) and (dia <= 29) then
idade:= (2021 - ano)
else
idade:= (2021 - (ano + 1));
writeln(idade);
end.
