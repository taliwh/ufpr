Alguém deseja cobrir as paredes de uma cozinha com azulejos. As lojas somente vendem caixas com 10 azulejos. Todas as lojas do ramo vendem apenas 3 (três) tipos de azulejos, cujas dimensões são:

50cm x 40cm;
50cm x 60cm;
50cm x 80cm.
Faça um programa Pascal que leia do teclado dois valores inteiros representando respectivamente o tipo do azulejo desejado (um dos números 1, 2 ou 3) e a área que se deseja azulejar, em metros quadrados. Seu programa deve imprimir a quantidade de caixas de azulejos que deverão ser compradas para cobrir toda a área. Considere que pedaços de azulejo podem ser reaproveitados, de maneira a minimizar a quantidade de caixas.

Exemplos:
Entrada 1:
2 122

Saída Esperada 1:
41 caixas

program Azulejos;
var
  tipo: integer;
  area, area_azulejo, qtd_azulejos, caixas: real;

begin
  // Leitura dos dados
  read(tipo, area);

  // Definição da área de um azulejo (em metros quadrados)
  if tipo = 1 then
    area_azulejo := 0.50 * 0.40
  else if tipo = 2 then
    area_azulejo := 0.50 * 0.60
  else if tipo = 3 then
    area_azulejo := 0.50 * 0.80
  else
  begin
    writeln('ERRO');
    halt;
  end;

  // Quantidade de azulejos necessários
  qtd_azulejos := area / area_azulejo;

  // Quantidade de caixas (cada caixa tem 10 azulejos)
  caixas := qtd_azulejos / 10;

  // Como só dá pra comprar caixas inteiras, usa arredondamento pra cima
  if frac(caixas) > 0 then
    caixas := trunc(caixas) + 1
  else
    caixas := trunc(caixas);

  // Impressão do resultado
  writeln(caixas:0:0, ' caixas');
end.
