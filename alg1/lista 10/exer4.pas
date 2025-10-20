//Dizemos que uma matriz quadrada inteira é um quadrado mágico se a soma dos elementos de cada linha, a soma dos elementos de cada coluna e a soma dos elementos das diagonais principal e secundária são todos iguais. Exemplo:

//8 0 7
//4 5 6
//3 10 2

//é um quadrado mágico pois 8+0+7 = 4+5+6 = 3+10+2 = 8+4+3 = 0+5+10 = 7+6+2 = 8+5+2 = 3+5+7 = 15.

//Crie um programa em Free Pascal que leia um valor n representando o tamanho da matriz e leia uma matrix A(n x n) que representa o quadrado e informe se a matriz é um quadrado mágico.

//Exemplo de entrada:
//3
//8 0 7
//4 5 6
//3 10 2

//Saída esperada para o exemplo acima:
//sim

program quadradomagico;
type
    matriz = Array[1..100,1..100] of integer;
var
    m: matriz;
    tam, valor: integer;

procedure lermatriz(tam: integer; var m: matriz);
var
    i,j: integer;
begin
    for i:= 1 to tam do
        for j:= 1 to tam do
            read(m[i,j]);
end;

procedure acharvalor(var valor: integer; var m: matriz; tam: integer);
var
    j: integer;
begin
    valor:= 0;
    for j:= 1 to tam do
        valor:= valor + m[1,j];
end;

function ehmagico(var m: matriz; tam, valor: integer): boolean;
var
    linhaok, i, somacol, somalin, colunaok, diagok, somadiag, somadiagsec, diagsecok, j: integer;
begin
    linhaok:= 0;
    colunaok:= 0;
    diagok:= 0;
    diagsecok:= 0;
    somadiag:= 0;
    somadiagsec:= 0;
    
    for i:= 2 to tam do
    begin  
        somalin:= 0;
        for j:= 1 to tam do
            somalin:= somalin + m[i,j];
        if somalin = valor then
            linhaok:= linhaok + 1;
    end;

    for j:= 1 to tam do
    begin
        somacol:= 0;
        for i:= 1 to tam do
            somacol:= somacol + m[i,j];
        if somacol = valor then
            colunaok:= colunaok + 1;
    end;
    //diagonal principal

    for i:= 1 to tam do
        somadiag:= somadiag + m[i,i];
    if somadiag = valor then
        diagok:= diagok + 1;

    // diagonal seucndaria
    i:= 1;
    j:= tam;
    while i <= tam do
    begin
        somadiagsec:= somadiagsec + m[i,j];
        j:= j - 1;
        i:= i + 1;
    end;

    if somadiagsec = valor then
        diagsecok:= diagsecok + 1;
    if (diagok = 1) and (diagsecok = 1) and (colunaok = tam) and (linhaok = (tam - 1)) then
        ehmagico:= true
    else
        ehmagico:= false;
end;
begin
    read(tam);
    lermatriz(tam, m);
    acharvalor(valor, m, tam);
    if ehmagico(m, tam, valor) then
        writeln('sim')
    else
        writeln('nao');
end.
