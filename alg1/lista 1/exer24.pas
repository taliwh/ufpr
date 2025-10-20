//Américo é um vendedor de tapetes caros, mas ele vende somente tapetes de alguns tamanhos. O estoque de Américo consiste em 3 tipos de tapetes: aqueles com comprimento de 1 até 3 metros e largura entre 1 e 4 metros; aqueles com comprimento entre 5 e 10 metros e largura entre 3 e 5 metros; e, por fim, aqueles com comprimentro entre 14 e 27 metros e largura entre 9 e 13 metros. Faça um programa Pascal que leia do teclado dois números inteiros, representando respectivamente o comprimento e a largura do tapete desejado, e imprima se Américo tem ou não o tapete.

//Exemplos:
//Entrada 1:
//1 1
//Saída Esperada 1:
//SIM

//Entrada 2:
//2 5
//Saída Esperada 2:
//NAO

//Entrada 3:
//17 13
//Saída Esperada 3:
//SIM

program hello;
var a, b: integer;
begin
read(a, b);
if (a < 3) and (b < 4) then
writeln('SIM')
else if ((a <= 10) and (a >= 5)) and ((b <= 5) and (b >= 3)) then
writeln('SIM')
else if ((a <= 27) and (a >= 14)) and ((b <= 13) and (b >= 9)) then
writeln('SIM')
else
writeln('NAO');
end.
