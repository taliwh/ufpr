// Faça um programa que leia um inteiro positivo n e em seguida leia n valores inteiros quaisquer e imprima "sim" se o vetor estiver ordenado em ordem crescente 
// e "nao" em caso contrário. Em qualquer caso, o programa também deve imprimir o vetor, mas na ordem inversa com relação à leitura.

program estudo;
type
    vetor = Array[1..100] of integer;
var
    v, rev: vetor;
    tam, i: integer;

procedure levetor(var v: vetor; tam: integer);
var 
    i, valor: integer;
begin
    for i:= 1 to tam do
    begin
        read(valor);
        v[i]:= valor;
    end;
end;

function ehordenado(var v: vetor; tam: integer): boolean;
var 
    i, desor, aux: integer;
begin
    desor:= 0;
    for i:= 1 to tam - 1 do
        if (v[i] > v[i + 1]) then 
            desor:= desor + 1;
    if (desor = 0) then
        ehordenado:= true
    else
        ehordenado:= false;
end;

procedure inverter(var rev, v: vetor; tam: integer);
var
    i, a: integer;
begin
    a:= 1;
    for i:= tam downto 1 do
    begin
        rev[a]:= v[i];
        a:= a + 1;
    end;
end;

begin
    read(tam);
    if (tam = 0) then
        writeln('vetor vazio')
    else 
    begin
        levetor(v, tam);
        if ehordenado(v, tam) then
        begin
            writeln('sim');
            inverter(rev, v, tam);
            for i:= 1 to tam do
                write(rev[i], ' ');
        end
        else
        begin
            writeln('nao');
            inverter(rev, v, tam);
            for i:= 1 to tam do
                write(rev[i], ' ');
        end;
    end;
end.
