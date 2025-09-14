//Faça um programa Pascal que leia do teclado dois números inteiros e imprima qual é o menor valor entre eles.

//Exemplos:
//Entrada 1:
//5 4
//Saída Esperada 1:
//4

//Entrada 2:
//-3 -4
//Saída Esperada 2:
//-4

//Entrada 3:
//6 15
//Saída Esperada 3:
//6

program Hello;
var a, b: integer;
begin
  read(a, b);
  if (a < b) then
  writeln (a)
  else
  writeln (b);
end.
