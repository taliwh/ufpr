//Faça um programa Pascal que leia do teclado um número inteiro e imprima SIM caso o número seja impar, negativo e menor que -20 ou então se for par, positivo e maior que 7. Caso contrário imprima NAO. A dica é usar uma combinação correta que envolva os operadores AND e OR.
//Observação: o operador MOD quando opera um número negativo, resulta em um valor negativo. Exemplo: -101 mod 2 resulta em -1.

//Exemplos:
//Entrada 1:
//17
//Saída Esperada 1:
//NAO

//Entrada 2:
//-101
//Saída Esperada 2:
//SIM

//Entrada 3:
//-13
//Saída Esperada 3:
//NAO

program hello;
var a: integer;
begin
read(a);
if (((a mod 2) <> 0) and (a < 0) and (a < 20)) or (((a mod 2) = 0) and (a > 0) and (a > 7)) then
writeln('SIM')
else
writeln('NAO');
end.
