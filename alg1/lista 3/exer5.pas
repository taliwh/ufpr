(* Faça um programa Pascal que leia do teclado uma quantidade arbitrária de números inteiros positivos terminada em zero e identifique o maior múltiplo de 7 (sete) entre esses números. Depois da leitura dos dados, o maior múltiplo de 7 encontrado deve ser impresso. O número zero serve para indicar o final da entrada e não deverá ser processado. Caso não haja nenhum múltipolo de sete na entrada o programa deve imprimir a mensagem NENHUM.

Exemplos:
Entrada 1:
4 8 3 63 99 41 28 99 65 0

Saída Esperada 1:
63

Entrada 2:
739 805 568 382 490 51 719 403 240 152 0

Saída Esperada 2:
805 *)

program multiplo7;
var
    valor, maiormult, mult, qtd: longint;
begin
    read(valor);
    maiormult:= -1;
    qtd:= 0;
    while valor <> 0 do
    begin
        if ((valor mod 7) = 0) then
        begin
            mult:= valor;
            qtd:= qtd + 1;
            if mult > maiormult then
                maiormult:= mult
            else
                maiormult:= maiormult;
        end;
        read(valor);
    end;
    if (qtd > 0) then
        writeln(maiormult)
    else
        writeln('NENHUM');
end.

