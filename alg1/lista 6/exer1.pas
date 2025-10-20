(* Faça uma função que receba como parâmetro um número inteiro e teste se ele é um número binário. Se ele for binário, imprima sim senão imprima nao. Teste sua função usando este código:

program testa_binario;
var n: longint;

(* coloque aqui o codigo da sua funcao que testa se eh binario *)

(* begin
    read (n);
    if eh_binario (n) then
        writeln ('sim')
    else
        writeln ('nao');
end.
Exemplos de entradas
10001
1020 *)

(* Saídas esperadas
sim
nao *) 

program testa_binario;
var n: longint;
function eh_binario(a:longint):boolean;
begin
    eh_binario:= true;
    while a >= 1 do
    begin
        if a mod 10 > 1 then
        begin
            eh_binario:= false;
            break;
        end;
        a:= a div 10;
    end;
end;    
begin
    read (n);
    if eh_binario (n) then
        writeln ('sim')
    else
        writeln ('nao');
end.
