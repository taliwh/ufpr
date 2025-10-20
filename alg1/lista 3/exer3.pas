(* Faça um programa Pascal que leia uma sequência de números reais terminada em 0 que representam a medida dos lados de um polígono e imprima "SIM" se ele é um polígono regular (todos os seus lados iguais) e "NAO" caso contrário.
Note que um polígono precisa ter ao menos 3 lados para ser um polígono O número zero serve para indicar o final da entrada de dados e não deve ser processado.

Exemplos:
Entrada 1:
1 2 3 0
Saida Esperada 1:
NAO

Entrada 2:
4 4 4 4 0
Saida Esperada 2:
SIM

Entrada 3:
4 4 0
Saida Esperada 3:
NAO *)

program poligono;
var
    valor, naoehpoligono, valorant, tam: longint;

begin
    read(valor);
    valorant:= valor;
    naoehpoligono:= 0;
    tam:= 1;
    while (valor <> 0) do
    begin
        if valorant <> valor then
            naoehpoligono:= naoehpoligono + 1;
        valorant:= valor;
        read(valor);
        tam:= tam + 1;
    end;
    if (tam < 4) or (naoehpoligono >= 1) then
        writeln('NAO')
    else
        writeln('SIM');
end.






