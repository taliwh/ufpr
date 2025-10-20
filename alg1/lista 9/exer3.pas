//Faça um programa em Free Pascal que leia um inteiro positivo n, sendo 1 ≤ m, n ≤ 100, e uma matriz
//inteira A n×n . O programa deve imprimir “sim” caso a matriz A seja de permutação, caso contrário deve
//imprimir “nao”.
//Nos casos de teste cada elemento x da matriz A é definido por 0 ≤ x ≤ 100.

//PS: Seu programa deve encerrar a execução assim que descobrir se a propriedade definida foi atendida ou não.

//Exemplo de entrada 1:
//3
//1 0 0
//0 1 0
//0 0 1

//Saı́da esperada para o exemplo acima:
//sim

//Exemplo de entrada 2:
//3
//1 0 0
//1 0 0
//0 1 0

//Saı́da esperada para o exemplo acima:
//nao

program permutacao;
type
    matriz = Array[1..100,1..100] of integer;
var
    tam: integer;
    m: matriz;
procedure lermatriz(var m: matriz; tam: integer);
var 
    i,j: integer;
begin
    for i:= 1 to tam do
        for j:= 1 to tam do
            read(m[i,j]);
end;

function permut(var m: matriz; tam: integer): boolean;
var
    zerolin, linhaok, colunaok, temumlin, temumcol, zerocol, i, j: integer;
begin
    linhaok:= 0;
    colunaok:= 0;
    for i:= 1 to tam do
    begin    
        temumlin:= 0;
        zerolin:= 0;
        for j:= 1 to tam do
        begin
            if (m[i,j] = 0) then
                zerolin:= zerolin + 1;
            if (m[i,j] = 1) then
                temumlin:= temumlin + 1;
        end;
        if (zerolin = (tam - 1)) and (temumlin = 1) then
            linhaok:= linhaok + 1;
    end;

    for j:= 1 to tam do
    begin    
        temumcol:= 0;
        zerocol:= 0;
        for i:= 1 to tam do
        begin
            if (m[i,j] = 0) then
                zerocol:= zerocol + 1;
            if (m[i,j] = 1) then
                temumcol:= temumcol + 1;
        end;
        if (zerocol = (tam - 1)) and (temumcol = 1) then
            colunaok:= colunaok + 1;
    end;
    if (linhaok = tam) and (colunaok = tam) then
        permut:= true
    else
        permut:= false;
end;

begin
    read(tam);
    lermatriz(m, tam);
    if permut(m, tam) then
        writeln('sim')
    else
        writeln('nao');
end.
    
