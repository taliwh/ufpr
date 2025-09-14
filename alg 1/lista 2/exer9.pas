Faça um programa Pascal que leia do teclado dois valores inteiros que são as coordenadas (X,Y) de um ponto no sistema cartesiano. Imprima na tela o quadrante ao qual o ponto pertence: 1, 2, 3 ou 4, conforme as regras clássicas da matemática.

Caso o ponto não pertenca a nenhum quandrante, imprima a letra X se ele está sobre o eixo X; imprima a letra Y se ele está sobre o eixo Y; ou então imprima a letra O, caso ele esteja na origem.

Exemplos:
Exemplo de entrada 1:
4 4
Saida Esperada 1:
1

Exemplo de entrada 2:
4 0
Saida Esperada 2:
X

program data;
var a, b: longint;
begin
  read(a, b);
  if (a = 0) and (b = 0) then
    writeln('O')
  else if (a = 0) then
    writeln('Y')
  else if (b = 0) then
    writeln('X')
  else if (a > 0) and (b > 0) then
    writeln('1')
  else if (a < 0) and (b > 0) then
    writeln('2')
  else if (a < 0) and (b < 0) then
    writeln('3')
  else if (a > 0) and (b < 0) then
    writeln('4');
end.
