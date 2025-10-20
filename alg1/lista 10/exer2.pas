//Um vetor real X com n elementos é apresentado como resultado de um sistema de equações lineares Ax = B cujos coeficientes são representados em uma matriz real A(m×n) e os lados direitos das equações (os resultados de cada equação) em um vetor real B de m elementos. Criar um programa em Free Pascal que verifique se o vetor X é realmente solução do sistema dado, imprimindo "sim" caso o vetor informado seja solução do sistema de equações, ou imprimindo "não" caso contrário.

//Dica: Comparações entre números reais pode ser um problema dependendo da arquitetura da máquina a ser utilizada. Para solucionar este problema um método a ser utilizado é a comparação por margem de erro.

//PS: O sistema apresentado no exemplo de entrada é representado pela seguinte equação:
//2x + y - 3z = -1
//-x + 3y + 2z = 12
//3x + y - 3z = 0

//Exemplo de entrada:
//3 3 #tamanho da matriz
//1 3 2 #resultado informado
//2 1 -3 #Matriz
//-1 3 2
//3 1 -3
//-1 12 0 #lado direito

//Saída esperada:
//sim

program exer1;
type
    matriz = Array[1..100,1..100] of integer;
    vetor =  Array[1..100] of integer;
var
    mat: matriz;
    vresultinformado, vdireito, vsoma: vetor;
    lin, col: integer;

procedure lematriz(lin, col: integer; var mat: matriz);
var
    i, j: integer;
begin
    for i:= 1 to lin do
        for j:= 1 to col do
            read(mat[i,j]);
end;

procedure levresultinformado(lin: integer; var vresultinformado: vetor);
var
    i: integer;
begin
    for i:= 1 to lin do
        read(vresultinformado[i]);
end;

procedure levdireito(lin: integer; var vdireito: vetor);
var
    i: integer;
begin
    for i:= 1 to lin do
        read(vdireito[i]);
end;

procedure somavetor(var vresultinformado, vsoma: vetor; var mat: matriz; lin, col: integer);
var
    x, i, j, soma: integer;
    matf: matriz;
begin
    x:= 1;
    for j:= 1 to col do
    begin
        for i:= 1 to lin do
            matf[i,j]:= vresultinformado[x] * mat[i,j]; 
        x:= x + 1;
    end;
    for i:= 1 to lin do
    begin
        soma:= 0;
        for j:= 1 to col do
            soma:= soma + matf[i,j];
        vsoma[i]:= soma;
    end;
end;

function verificaigualdade(lin: integer; var vsoma, vdireito: vetor): boolean;
var
    igual, i: integer;
begin
    igual:= 0;
    i:= 1; 
    for i:= 1 to lin do
        if vsoma[i] = vdireito[i] then
            igual:= igual + 1;
    if (igual = lin) then
        verificaigualdade:= true
    else
        verificaigualdade:= false;
end;

begin
    read(lin, col);
    levresultinformado(lin, vresultinformado);
    lematriz(lin, col, mat);
    levdireito(lin, vdireito);
    somavetor(vresultinformado, vsoma, mat, lin, col);
    if verificaigualdade(lin, vsoma, vdireito) then
        writeln('sim')
    else
        writeln('nao');
end.
