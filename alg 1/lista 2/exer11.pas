Faça um programa Pascal que leia do teclado um conjunto de 4 valores i, a, b, c, sendo que i é um valor inteiro e positivo e a, b, c, são quaisquer valores reais. Imprima na tela os valores de a, b, c da seguinte forma:

os três valores a, b, c em ordem crescente, se i = 1
os três valores a, b, c em ordem decrescente, se i = 2,
os três valores a, b, c de forma que o maior dentre a, b, c fique entre os outros dois valores, com a ordem relativa entre os outros dois deles mantida, se i = 3. Observe no exemplo de teste 2 que o maior valor (68) foi impresso na saída esperada no meio, e os valores 5 e 45 ficaram na mesma ordem relativa, isto é, o 5 aparece antes do 45 na saída porquê na entrada eles estavam nesta ordem.
Exemplos:

Exemplo 1:
1 34 12 21

Saida Esperada 1:
12 21 34

Exemplo 2:
3 68 5 45

Saida Esperada 2:
5 68 45

program OrganizaValores;
var
  i: integer;
  a, b, c, maior: real;

begin

  read(i, a, b, c);


  if i = 1 then
  begin

    if (a <= b) and (b <= c) then
      writeln(a:0:0, ' ', b:0:0, ' ', c:0:0)
    else if (a <= c) and (c <= b) then
      writeln(a:0:0, ' ', c:0:0, ' ', b:0:0)
    else if (b <= a) and (a <= c) then
      writeln(b:0:0, ' ', a:0:0, ' ', c:0:0)
    else if (b <= c) and (c <= a) then
      writeln(b:0:0, ' ', c:0:0, ' ', a:0:0)
    else if (c <= a) and (a <= b) then
      writeln(c:0:0, ' ', a:0:0, ' ', b:0:0)
    else
      writeln(c:0:0, ' ', b:0:0, ' ', a:0:0)
  end
  else if i = 2 then
  begin

    if (a >= b) and (b >= c) then
      writeln(a:0:0, ' ', b:0:0, ' ', c:0:0)
    else if (a >= c) and (c >= b) then
      writeln(a:0:0, ' ', c:0:0, ' ', b:0:0)
    else if (b >= a) and (a >= c) then
      writeln(b:0:0, ' ', a:0:0, ' ', c:0:0)
    else if (b >= c) and (c >= a) then
      writeln(b:0:0, ' ', c:0:0, ' ', a:0:0)
    else if (c >= a) and (a >= b) then
      writeln(c:0:0, ' ', a:0:0, ' ', b:0:0)
    else
      writeln(c:0:0, ' ', b:0:0, ' ', a:0:0)
  end
  else if i = 3 then
  begin

    maior := a;
    if b > maior then maior := b;
    if c > maior then maior := c;

    if (maior = a) then
      writeln(b:0:0, ' ', a:0:0, ' ', c:0:0)
    else if (maior = b) then
      writeln(a:0:0, ' ', b:0:0, ' ', c:0:0)
    else
      writeln(a:0:0, ' ', c:0:0, ' ', b:0:0);
  end;
end.
