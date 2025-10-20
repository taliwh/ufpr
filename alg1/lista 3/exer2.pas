(* 
Faça um programa Pascal que calcule o valor da soma dos quadrados dos primeiros 50 inteiros positivos não nulos e imprima o resultado do cálculo na tela.
Observe que este programa não tem entrada, apenas saída. *)

program somatorio;
var
    i, soma, num: longint;

begin
    soma:= 0;
    for i:= 1 to 50 do
    begin
        num:= i * i;
        soma:= soma + num;
    end;
    writeln(soma);
end.
