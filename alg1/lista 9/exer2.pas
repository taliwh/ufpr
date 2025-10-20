//Faça um programa em Free Pascal que leia um inteiro positivo n, sendo 1 ≤ m, n ≤ 100, e uma matriz inteira A n×n . O programa deve imprimir “sim” caso a matriz A seja triangular, caso contrário deve imprimir “nao”.
//Nos casos de teste cada elemento x da matriz A é definido por 0 ≤ x ≤ 100.

//PS: Seu programa deve encerrar a execução assim que descobrir se a propriedade definida foi atendida ou não.

//Exemplo de entrada 1:
//3
//1 9 5
//0 2 4
//0 0 7

//Saı́da esperada para o exemplo acima:
//sim

//Exemplo de entrada 2:
//3
//1 0 0
//5 2 0
//4 9 3
//Saı́da esperada para o exemplo acima:
//sim

//Exemplo de entrada 2:
//3
//1 2 3
//4 5 6
//7 8 9
//Saı́da esperada para o exemplo acima:
//nao

program matriztriangular;
type
    matriz = Array[1..100,1..100] of integer;
var
    m: matriz;
    tam: integer;

procedure lermatriz(var m: matriz; tam: integer);
var 
    i, j, valor: integer;
begin
    for i:= 1 to tam do
        for j:= 1 to tam do
        begin
            read(valor);
            if (valor >= 0) and (valor <= 100) then
                m[i,j]:= valor;
        end;
end;

function ehtriangular(var m: matriz; tam: integer): boolean;
var 
     i, j, elemento1, elemento2: integer;
begin 
    elemento1:= 0;
    elemento2:= 0;
    for j:= 1 to tam - 1 do
        for i:= j + 1 to tam do
            if (m[i,j] = 0) then
                elemento1:= elemento1 + 1;
    for j:= tam downto 2 do
        for i:= j - 1 downto 1 do
            if (m[i,j] = 0) then
                elemento2:= elemento2 + 1;
    if (elemento1 = ((tam * (tam - 1)) div 2)) or (elemento2 = ((tam * (tam - 1)) div 2)) then
        ehtriangular:= true
    else
        ehtriangular:= false;
end;

begin
    read(tam);
    lermatriz(m, tam);
    if ehtriangular(m, tam) then
        writeln('sim')
    else
        writeln('nao');
end.
