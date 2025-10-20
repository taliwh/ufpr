//Faça um programa Pascal que leia dois números inteiros do teclado e efetue a adição. Caso o valor somado seja maior que 20, este deverá ser apresentado somando-se a ele mais 8; caso o valor somado seja menor ou igual a 20, este deverá ser apresentado subtraindo-se 5.

//Exemplos:
//Entrada 1:
//13 5
//Saída Esperada 1:
//13

//Entrada 2:
//-3 -4
//Saída Esperada 2:
//-12

//Entrada 3:
//16 5
//Saída Esperada 3:
//29

program hello;
var a, b, calculo, resultado: integer;
begin
read(a, b);
calculo:= a + b;
if calculo > 20 then
resultado:= calculo + 8
else
resultado:= calculo - 5;
writeln(resultado);
end.
