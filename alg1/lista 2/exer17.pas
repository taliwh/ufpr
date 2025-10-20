Faça um programa Pascal que receba um número inteiro positivo N e calcule o produto dos N primeiros números pares positivos. Ao final, imprima um inteiro que é este produto. Para esse exercício, considere o primeiro número par como sendo 2.

Exemplos:
Entrada 1:
2
Saída Esperada 1:
8

Entrada 2:
4
Saída Esperada 2:
384

program data;
var n, i, produto, multiplicador: longint;
begin
      read(n); 
      produto:= 1;
      multiplicador:= 2;
      for i:= 1 to n do
      begin
      produto:= produto * multiplicador;
      multiplicador:= multiplicador + 2;
      end;
      writeln(produto);
end.
      
