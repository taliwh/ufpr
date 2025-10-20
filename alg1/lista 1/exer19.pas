//Faça um programa Pascal que leia um número inteiro, calcule se ele é divisível por 3 e por 7. Caso seja, imprima SIM e caso não seja imprima NAO. Dica: use o operador AND.

//Exemplos:
//Entrada 1:
//21
//Saída Esperada 1:
//SIM

//Entrada 2:
//7
//Saída Esperada 2:
//NAO

//Entrada 2:
//-3
//Saída Esperada 2:
//NAO

program Hello;
var a: longint;
begin
  read(a);
  if ((a mod 7) = 0) and ((a mod 3) = 0) then 
  writeln('SIM')
  else
  writeln('NAO');
end.
