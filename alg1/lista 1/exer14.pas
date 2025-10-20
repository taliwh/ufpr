//Faça um programa Pascal que leia de teclado um número inteiro e imprima SIM se este é múltiplo de 3 e NAO caso contrário.

//Exemplos:
//Entrada 1:
//5
//Saída Esperada 1:
//NAO

//Entrada 2:
//-3
//Saída Esperada 2:
//SIM

//Entrada 3:
//15
//Saída Esperada 3:
//SIM

program Hello;
var a: longint;
begin
  read(a);
  if (a mod 3) = 0 then
  writeln('SIM')
  else
  writeln('NAO');
end.
