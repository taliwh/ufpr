//Faça um programa em Free Pascal que leia dois inteiros positivos m e n, sendo 1 ≤ m, n ≤ 100, e uma matriz A m×n . O programa deve imprimir “sim” se há elementos repetidos na matriz A, caso contrário deve imprimir “nao”.
//Nos casos de teste cada elemento x da matriz A é definido por 1 ≤ x ≤ 1000.

//PS: Seu programa deve encerrar a execução assim que descobrir se a propriedade definida foi atendida ou não.

//Exemplo de entrada 1:

//3 3
//1 2 3
//4 5 6
//7 8 9

//Saída esperada para o exemplo acima:
//nao

//Exemplo de entrada 2:

//3 4
//1 2 3 4
//4 5 6 7
//7 8 9 10

//Saída esperada para o exemplo acima:
//sim

program repeticao;
type
    matriz = Array[1..100,1..100] of integer;
var
    mat: matriz;
    linf, colf, linin, colin, i, j, novalin, novacol: integer;

procedure lermatriz(var mat: matriz; linf, colf: integer);
var 
    i,j: integer;
begin
    for i:= 1 to linf do
        for j:= 1 to colf do
            read(mat[i,j]);
end;

function buscarepeticao(var mat: matriz; x, linf, colf, linin, colin: integer): boolean;
var
    i, j: integer;
    achou: boolean;
begin
    i:= linin;
    j:= colin;
    achou:= false;
    while (i <= linf) and (not achou) do
    begin
        while (j <= colf) and (not achou) do
        begin
            if (mat[i,j] = x) then
                achou:= true;
            j:= j + 1;
        end;
        i:= i + 1;
        j:= 1;
    end;
    buscarepeticao:= achou;
end;

    
procedure proxtermo(i, j, linf, colf: integer; var novalin, novacol: integer);
begin
    if j = colf then
    begin
        novalin:= i + 1;
        novacol:= 1;
    end
    else
    begin
        novacol:= j + 1;
        novalin:= i;
    end;
end;


function temrepeticao(var mat: matriz; linf, colf: integer): boolean;
var
    i,j: integer;
    repetiu: boolean;
begin
    repetiu:= false;
    i:= 1;
    while (i <= linf) and (not repetiu) do
    begin
        j:= 1;
        while (j <= colf) and (not repetiu) do
        begin
            proxtermo(i, j, linf, colf, novalin, novacol);
            repetiu:= buscarepeticao(mat, mat[i,j], linf, colf, novalin, novacol);
            j:= j + 1;
        end;
        i:= i + 1;
    end;
    temrepeticao:= repetiu;
end;

begin
    read(linf, colf);
    lermatriz(mat, linf, colf);
    if temrepeticao(mat, linf, colf) then
        writeln('sim')
    else
        writeln('nao');
end.
