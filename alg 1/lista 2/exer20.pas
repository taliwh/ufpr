Faça um programa Pascal que receba um número positivo N e imprima na tela a soma dos N primeiros números da sequência de Fibonacci. Os dois primeiros números da sequência são 0 e 1, e os próximos são dados pela soma dos dois últimos números anteriormente calculados.

A título de exemplo, os oito primeiros valores dessa sequência são: 0, 1, 1, 2, 3, 5, 8, 13.

Exemplos:
Entrada 1:
3
Saída Esperada 1:
2

Entrada 2:
5
Saída Esperada 2:
7

program fibonacci;
var
    tam, termo1, termo2, i, prox, soma: integer;
begin
    read(tam);
    if (tam = 1) or (tam = 2) then
        writeln(tam)
    else
    begin
        termo1:= 0;
        termo2:= 1; 
        i:= 1;
        soma:= 1;
        while i <= (tam - 2) do
        begin                  // 0 1 1 2 3 5 8
            prox:= termo1 + termo2;
            soma:= soma + prox;
            termo1:= termo2;
            termo2:= prox;
            i:= i + 1;
        end;
        writeln(soma);
    end;
end.
