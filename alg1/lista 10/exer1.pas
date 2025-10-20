//Uma matriz D(8 × 8) pode representar a posiçao atual de um jogo de damas, sendo que 0 
//indica uma casa vazia, 1 indica uma casa ocupada por uma peça branca e -1 indica uma casa ocupada por uma peça preta. Supondo que as peças pretas estão se movendo no sentido crescente das linhas da matriz D, determinar as posições das peças pretas que:

//• podem tomar peças brancas;
//• podem mover-se sem tomar peças brancas;
//• não podem se mover.

//A prioridade na ação é sempre tomar uma peça, ou seja, em uma situação na qual uma peça preta possa tanto "mover" quanto "tomar", esta peça é marcada como "tomar". Cada peça só pode ser marcada com uma ação.

//Para este exercício, considere que as peças pretas nunca estarão na última linha do jogo (dama). Caso não ocorra peça para algum dos movimentos possíveis exibir o valor 0 (zero) ao invés da posição.

//Exemplo de Entrada 1:
//-1 0 -1 0 -1 0 -1 0
//0 -1 0 -1 0 -1 0 -1
//-1 0 -1 0 -1 0 -1 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//0 1 0 1 0 1 0 1
//1 0 1 0 1 0 1 0
//0 1 0 1 0 1 0 1

//Saída esperada para a entrada acima:
//tomar: 0
//mover: 3-1 3-3 3-5 3-7
//ficar: 1-1 1-3 1-5 1-7 2-2 2-4 2-6 2-8

//Exemplo de Entrada 2:
//-1 0 -1 0 -1 0 -1 0
//0 -1 0 -1 0 -1 0 -1
//0 0 -1 0 -1 0 -1 0
//0 -1 0 0 0 0 0 0
//0 0 1 0 0 0 0 0
//0 1 0 0 0 1 0 1
//1 0 1 0 1 0 1 0
//0 1 0 1 0 1 0 1

//Saída esperada para a entrada acima:
//tomar: 4-2
//mover: 2-2 3-3 3-5 3-7
//ficar: 1-1 1-3 1-5 1-7 2-4 2-6 2-8

program jogodedamas;
type
    matriz = Array[1..8,1..8] of integer;
    coordenadas = record //registro de coordenadas 
        linha: integer;
        coluna: integer;
    end;
    listatomar = Array[1..100] of coordenadas; 
    listaficar = Array[1..100] of coordenadas; 
    listamover = Array[1..100] of coordenadas; 

var
    preta, branca, vazio, count, tamtomar, i, tammexer, tampresa: integer;
    m: matriz;
    tomar: listatomar;
    ficar: listaficar;
    mover: listamover;

procedure lermatriz(var m: matriz);
var
    i, j: integer;
begin
    for i:= 1 to 8 do
        for j:= 1 to 8 do
            read(m[i,j]);
end;

procedure comer(var tomar: listatomar; var tamtomar: integer; preta, branca: integer);
var
    i, j: integer;
    podeComerEsq, podeComerDir: boolean;
begin
    for i := 1 to 7 do  // mesma ideia: i+1 não pode passar de 8
        for j := 1 to 8 do
            if m[i,j] = preta then
            begin
                podeComerEsq := (j > 1) and (m[i+1, j-1] = branca);
                podeComerDir := (j < 8) and (m[i+1, j+1] = branca);

                if podeComerEsq or podeComerDir then
                begin
                    tamtomar := tamtomar + 1;
                    tomar[tamtomar].linha := i;
                    tomar[tamtomar].coluna := j;
                end;
            end;
end;


procedure mexer(var mover: listamover; var tammexer: integer; preta, vazio: integer);
var
    i, j: integer;
    podeEsq, podeDir: boolean;
begin
    for i:= 1 to 7 do  
        for j:= 1 to 8 do
            if m[i,j] = preta then
            begin
                podeEsq := (j > 1) and (m[i+1, j-1] = vazio);
                podeDir := (j < 8) and (m[i+1, j+1] = vazio);

                if podeEsq or podeDir then
                begin
                    tammexer := tammexer + 1;
                    mover[tammexer].linha := i;
                    mover[tammexer].coluna := j;
                end;
            end;
end;

procedure presa(var ficar: listaficar; var tampresa: integer; preta, branca: integer);
var
    i, j: integer;
    cimaesq, cimadir, baixesq, baixedir: integer;
begin
    for i := 1 to 8 do
        for j := 1 to 8 do
            if m[i, j] = preta then
            begin
                cimaesq := (m[i-1, j-1]);
                cimadir := (m[i-1, j+1]);
                baixesq := (m[i+1, j-1]);
                baixedir := (m[i+1, j+1]);
                
                if ((cimaesq <> 0) and (cimadir <> 0) and (baixesq <> 0) and (baixedir <> 0)) or ((cimaesq <> 0) and (baixesq <> 0) and (j = 8)) or ((cimadir <> 0) and (baixedir <> 0) and (j = 1)) or (((j=1) and (i=1)) and (baixedir <> 0)) or (((j=8) and (i=1)) and (baixesq <> 0)) or ((i=1) and (baixesq <> 0) and (baixedir <> 0)) then
                begin
                    tampresa := tampresa + 1;
                    ficar[tampresa].linha := i;
                    ficar[tampresa].coluna := j;
                end;
            end;
end;

procedure imprime(var tomar: listatomar; var ficar: listaficar; var mover: listamover; tammexer, tampresa, tamtomar: integer);
var
    i: integer;
begin
    write('tomar: ');
    if tamtomar > 0 then
        for i:= 1 to tamtomar do
            write(tomar[i].linha, '-', tomar[i].coluna, ' ')
    else
        write(0);
    writeln;

    write('mover: ');
    if tammexer > 0 then
        for i:= 1 to tammexer do
            write(mover[i].linha, '-', mover[i].coluna, ' ')
    else
        write(0);
    writeln;

    write('ficar: ');
    if tampresa > 0 then
        for i:= 1 to tampresa do
            write(ficar[i].linha, '-', ficar[i].coluna, ' ')
    else
        write(0);
    writeln;
end;
 
procedure remove_mover_duplicado(var mover: listamover; var tammexer: integer; tomar: listatomar; tamtomar: integer);
var
    i, j, k: integer;
    achou: boolean;
begin
    i := 1;
    while i <= tammexer do
    begin
        achou := false;
        for j := 1 to tamtomar do
            if (mover[i].linha = tomar[j].linha) and (mover[i].coluna = tomar[j].coluna) then
                achou := true;
        
        if achou then
        begin
            for k := i to tammexer - 1 do
                mover[k] := mover[k + 1];
            tammexer := tammexer - 1;          
        end
        else
            i := i + 1;
    end;
end;

begin
    tamtomar:= 0;
    tammexer:= 0;
    tampresa:= 0;
    lermatriz(m);
    comer(tomar, tamtomar, -1, 1);
    mexer(mover, tammexer, -1, 0);
    presa(ficar, tampresa, -1, 1);
    remove_mover_duplicado(mover, tammexer, tomar, tamtomar);
    imprime(tomar, ficar, mover, tammexer, tampresa, tamtomar);
end.
