Um banco concederá um crédito especial aos seus clientes, mas este crédito será dependente do saldo médio de cada cliente no último ano. Faça um programa Pascal que leia do teclado um valor inteiro que é o saldo médio de um cliente específico e calcule o valor do crédito de acordo com a tabela abaixo. Imprima na tela um inteiro que é o saldo médio lido e outro valor inteiro que é o valor do crédito que pode ser concedido.
Observação: este último valor impresso deverá ser seguido do símbolo "%", a menos da situação em que este crédito é zero, neste caso não deve ser impresso este símbolo.

Saldo médio	Percentual
de 0 a 200	0
de 201 a 400	20% do valor do saldo médio
de 401 a 600	30% do valor do saldo médio
acima de 601	40% do valor do saldo médio
Exemplos:
Exemplo 1:
150

Saida Esperada 1:
150
0

Exemplo 2:
1000

Saida Esperada 2:
1000
40%

program CreditoEspecial;

var
  saldoMedio: integer;
  percentual: integer;

begin
  readln(saldoMedio);

  if (saldoMedio <= 200) then
    percentual := 0
  else if (saldoMedio <= 400) then
    percentual := 20
  else if (saldoMedio <= 600) then
    percentual := 30
  else
    percentual := 40;

  writeln(saldoMedio);
  if percentual = 0 then
    writeln(0)
  else
    writeln(percentual, '%');
end.
