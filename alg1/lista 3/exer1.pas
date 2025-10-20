//Faça um programa Pascal que leia do teclado um conjunto de números onde cada linha contém dois valores numéricos sendo o primeiro do tipo real e o segundo do tipo inteiro. O segundo valor é o peso atribuído ao primeiro valor. O programa deve calcular e imprimir com duas casas decimais a média ponderada dos diversos valores lidos. A última linha de dados contém dois números zero. Esta linha não deve ser considerada no cálculo da média e serve apenas para marcar o final da entrada de dados.

//Isto é, calcular o seguinte, supondo que m linhas foram digitadas:

//(n1 * p1 + n2 * p2 + ... + nm * pm) / (p1 + p2 + ... + pm)

//Imprima o resultado com duas casas decimais.

//Exemplos:
(* Entrada 1:
60 1
30 2
40 3
0 0
Saída esperada 1:
40.00 *)

program sim;
var
    num, mult, media, somanum, somaden: real;
    p: longint;

begin
    somanum:= 0;
    somaden:= 0;
    read(num,p);
    while ((num <> 0) or (p <> 0)) do
    begin
        mult:= num * p;
        somanum:= mult + somanum;
        somaden:= p + somaden;
        read(num, p);
    end;
    media:= somanum / somaden;
    writeln(media:2:2);
end.


