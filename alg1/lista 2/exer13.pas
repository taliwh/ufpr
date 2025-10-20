Uma empresa concederá um aumento de salário aos seus funcionários, mas este aumento será de acordo com o cargo que cada um ocupa. A tabela abaixo contém os códigos, o cargo e e percentual de aumento correspondente.
Faça um programa Pascal que leia dois valores do teclado, o primeiro é um número real que informa o salário de um funcionário e o segundo é um número inteiro que informa o código do cargo dele. Calcule o valor do novo salário e o imprima na tela com duas casas decimais.
Se o cargo do funcionário não estiver na tabela, ele deverá receber 40% de aumento. Imprima o valor do salário antigo, o do novo salário e a diferença entre eles, nesta ordem, em 3 linhas, todos eles sempre valores reais com duas casas decimais.

Código	Cargo	Percentual
101	Gerente	10%
102	Engenheiro	20%
103	Técnico	30%
Exemplos:
Exemplo 1:
2500 101

Saida Esperada 1:
2500.00
2750.00
250.00

Exemplo 2:
5000 102

Saida Esperada 2:
5000.00
6000.00
1000.00

program AumentoSalario;
var
  salario_antigo, salario_novo, aumento: real;
  codigo: integer;

begin
  // Leitura do salário e código
  read(salario_antigo, codigo);

  // Cálculo do aumento conforme o código
  if codigo = 101 then
    aumento := salario_antigo * 0.10
  else if codigo = 102 then
    aumento := salario_antigo * 0.20
  else if codigo = 103 then
    aumento := salario_antigo * 0.30
  else
    aumento := salario_antigo * 0.40;

  // Novo salário
  salario_novo := salario_antigo + aumento;

  // Impressão dos resultados
  writeln(salario_antigo:0:2);
  writeln(salario_novo:0:2);
  writeln(aumento:0:2);
end.
