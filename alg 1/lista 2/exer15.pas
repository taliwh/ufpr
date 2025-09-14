Faça um programa Pascal que leia do teclado um valor real que representa o salário mensal de uma pessoa. Seu programa deve imprimir valor do imposto de renda (IR) mensal, em reais, de acordo com a tabela de 2009, que está abaixo.

Se o salário digitado for menor que o salário mínimo de R$ 540,00 o programa deve imprimir "NAO".

menor ou igual a 1424,00: 0%;
maior que 1424,00, menor ou igual a 2150,00: 7.5%;
maior que 2150,00, menor ou igual a 2866,00: 15%;
maior que 2866,00, menor ou igual a 3582,00: 22.5%;
maior que 3582,00: 27.5%.
Junto com o valor do IR mensal, o programa deve imprimir a Faixa (1,2,3,4 ou 5) correspondente ao salário.

Exemplos:
Entrada 1:
500.00

Saída Esperada 1:
NAO

Entrada 2:
2300.00

Saída Esperada 2:
3 345.00

program ImpostoDeRenda;
var
  salario, ir: real;
  faixa: integer;

begin
  // Leitura do salário
  read(salario);

  // Verifica se é menor que salário mínimo
  if salario < 540.00 then
    writeln('NAO')
  else
  begin
    // Determina faixa e calcula IR
    if salario <= 1424.00 then
    begin
      faixa := 1;
      ir := 0.00;
    end
    else if salario <= 2150.00 then
    begin
      faixa := 2;
      ir := salario * 0.075;
    end
    else if salario <= 2866.00 then
    begin
      faixa := 3;
      ir := salario * 0.15;
    end
    else if salario <= 3582.00 then
    begin
      faixa := 4;
      ir := salario * 0.225;
    end
    else
    begin
      faixa := 5;
      ir := salario * 0.275;
    end;

    // Impressão dos resultados
    writeln(faixa, ' ', ir:0:2);
  end;
end.
