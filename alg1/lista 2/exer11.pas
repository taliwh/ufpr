Um vendedor necessita de um programa que calcule o preço total devido por um cliente que comprou um produto em sua loja. Faça um programa Pascal que receba dois números inteiros que são, respectivamente, o código do produto e a quantidade comprada. Imprima na tela o preço total com duas casas decimais, usando a tabela abaixo.
Caso o código não exista o programa deve imprimir ERRO.

Código do Produto	Preço unitário
1001	5,32
1324	6,45
6548	2,37
987	5,32
7623	6,45
Exemplos:
Exemplo 1:
1324 6
Saida Esperada 1:
38.70

Exemplo 2:
987 9
Saida Esperada 2:
47.88

program CalculaPreco;
var
  codigo, quantidade: integer;
  preco, total: real;

begin
  read(codigo, quantidade);
  if codigo = 1001 then
    preco := 5.32
  else if codigo = 1324 then
    preco := 6.45
  else if codigo = 6548 then
    preco := 2.37
  else if codigo = 987 then
    preco := 5.32
  else if codigo = 7623 then
    preco := 6.45
  else
  begin
    writeln('ERRO');
    halt;
  end;


  total := preco * quantidade;

  writeln(total:0:2);
end.
