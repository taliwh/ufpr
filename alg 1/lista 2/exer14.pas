Faça um programa Pascal que leia dois números inteiros representando respectivamente o número de lados de um polígono regular e a medida do lado. Seu programa deve fazer o seguinte:

se o número de lados for 3, imprima TRIANGULO e o valor do seu perímetro;
se o número de lados for 4, imprima QUADRADO e o valor da sua área;
se o número de lados for 5, imprima PENTAGONO;
se o número de lados for menor que 3 imprima a mensagem "ERRO";
se o número de lados for maior que 5 imprima a mensagem "ERRO".
Exemplos:
Exemplo 1:
3 10

Saida Esperada 1:
TRIANGULO 30

Exemplo 2:
6 20

Saida Esperada 2:
ERRO

program Poligono;
var
  lados, medida, perimetro, area: integer;

begin
  // Leitura dos valores
  read(lados, medida);

  // Verifica quantidade de lados e executa ação correspondente
  if lados = 3 then
  begin
    perimetro := 3 * medida;
    writeln('TRIANGULO ', perimetro);
  end
  else if lados = 4 then
  begin
    area := medida * medida;
    writeln('QUADRADO ', area);
  end
  else if lados = 5 then
    writeln('PENTAGONO')
  else
    writeln('ERRO');
end.
