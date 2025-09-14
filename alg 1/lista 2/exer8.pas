Sabendo-se que a água se solidifica a zero grau Celsius, ou a 32 Fahrenheit, e que entra em ebulição a 100 graus Celsius ou 212 Fahrenheit, faça um programa Pascal que obtenha do teclado um inteiro que é o valor de temperatura em Fahrenheit e imprima na tela o valor correspondente em Celsius e também imprima na tela uma mensagem "solido", "liquido" ou "gasoso" indicando respectivamente se a água está no estado sólido, líquido ou gasoso.

A fórmula de conversão entre graus Celsius e Farenheit é:

5f - 9c - 160 = 0

Exemplos:
Entrada 1:
45

Saída Esperada 1:
7.22
liquido

Entrada 2:
240

Saída Espearada 2:
115.56
gasoso

program data;
var a, calculo: real;
begin
      read(a);
      calculo:= (5/9) * (a - 32);
      if (calculo <= 0) then
      begin
      writeln(calculo:0:2);
      writeln('solido');
      end
      else if ((calculo < 100) and (calculo > 0)) then
      begin
      writeln(calculo:0:2);
      writeln('liquido');
      end
      else if (calculo >= 100) then
      begin
      writeln(calculo:0:2);
      writeln('gasoso');
      end;
end.
