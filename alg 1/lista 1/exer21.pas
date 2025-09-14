//Faça um programa Pascal que leia um número inteiro do teclado, calcule se ele é ou não divisível por 5. Imprima SIM caso ele seja e NAO em caso contrário.

//Exemplos:
//Entrada 1:
//5
//Saída Esperada 1:
//SIM

//Entrada 2:
//-5
//Saída Esperada 2:
//SIM

//Entrada 3:
//3
//Saída Esperada 3:
//NAO

program divisao;
var a: longint;
begin
read(a);
if (a mod 5) = 0 then
writeln('SIM')
else
writeln('NAO');
end.
