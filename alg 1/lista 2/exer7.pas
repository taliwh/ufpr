Faça um programa Pascal que leia do teclado um valor inteiro que é a área de um cômodo e imprima um valor inteiro que é potência de iluminação necessária para iluminá-lo de acordo com a seguinte relação:

100 watts para os comodos com 6m quadrado ou menos
80 watts para os primeiros 3 m quadrado e mais 15 watts a cada 1m quadrado de acrescimo para comodos maiores

Exemplos:
Entrada 1:
5
Saida Esperada 1:
100

Entrada 2:
9
Saida Esperada 2:
170

program data;
var a, potencia: integer;
begin
read(a);
potencia:= ((a - 3) * 15) + 80;
if (a <= 6) then
writeln('100');
if (a > 6) then
writeln(potencia);
end.
