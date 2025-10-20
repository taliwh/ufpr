//Faça um programa em Free Pascal que leia dois inteiros positivos m e n, sendo 1 ≤ m, n ≤ 100, e uma matriz A m×n . O programa deve imprimir o números de linhas e o número de colunas que são nulas, ou seja, quando todos os elementos de uma linha ou coluna são iguais a 0 (zero).
//Nos casos de teste cada elemento x da matriz A é definido por 0 ≤ x ≤ 100.

//Exemplo de entrada:
//4 4
//1 0 2 3
//4 0 5 6
//0 0 0 0
//0 0 0 0

//Saı́da esperada para o exemplo acima:
//linhas: 2
//colunas: 1

program matriznula;
type
    matriz = Array[1..100,1..100] of integer;
var
    lin1, col1, linnula, colnula: integer;
    m1: matriz;

procedure lermatriz(lin1, col1: integer; var m1: matriz);
var
    i,j: integer;
begin
    for i:=1 to lin1 do 
        for j:=1 to col1 do
        read(m1[i,j]);
end;

procedure achanulo(var m1: matriz; lin1, col1: integer; var linnula, colnula:integer);
var
    i,j, zerolin, zerocol: integer;
begin
    colnula:= 0;
    linnula:= 0;
    for i:=1 to lin1 do 
    begin
        zerocol:= 0;
        for j:=1 to col1 do
            if (m1[i,j] = 0) then
                zerocol:= zerocol + 1;
        
        if (zerocol = col1) then
            linnula:= linnula + 1;
    end;

    for j:=1 to col1 do
    begin
        zerolin:= 0;
        for i:=1 to lin1 do
        begin
            if (m1[i,j] = 0) then
                zerolin:= zerolin + 1;
        end;
        if (zerolin = lin1) then
            colnula:= colnula + 1;
    end;
end;


begin
    read(lin1,col1);
    lermatriz(lin1, col1, m1);
    achanulo(m1, lin1, col1, linnula, colnula);
    writeln('linhas: ', linnula);
    writeln('colunas: ', colnula);
end.
