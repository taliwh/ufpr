//Faça um programa que leia uma sequência de códigos de operação e valor, onde o código de operação é um inteiro com os seguintes valores:

//0 (zero): fim
//1 (um): inserção
//2 (dois): remoção

//O valor lido é um número real que deve ser inserido em um vetor (caso a operação seja 1), ou removido do vetor (caso a operação seja 2). As
//inserções no vetor devem ser realizadas de forma que o vetor esteja sempre ordenado. O programa deve imprimir todos os vetores resultantes de cada operação e ao final deve imprimir o vetor resultante. Imprima os valores reais sempre com uma casa decimal. Caso o vetor esteja vazio, imprima a mensagem "vazio".

//Detalhamento:

//A quantidade máxima de valores que pode ser inserida é 200;
//Se a quantidade máxima for ultrapassada o programa deve dar uma mensagem de erro (imprima a mensagem "erro");
//Se for requisitada a remoção de um número não existente o programa deve dar uma mensagem de erro (imprima "erro");
//Se o código de operação for inválido o programa deve continuar lendo um novo código até que ele seja 0 (zero), 1 (um) ou 2 (dois).
//Use ao máximo funções e procedimentos apropriados 

program insercaoremocao;
type
    vetor = Array[1..200] of real;
var
    v: vetor;
    valor, num: real;
    tam: integer;
    achou: boolean;

procedure inserir(var tam: integer; var v: vetor; num: real);
begin
    tam:= tam + 1;
    v[tam]:= num;
end;

procedure remover(var v: vetor; var tam: integer; var achou: boolean; num: real);
var
    i: integer;
begin
    achou:= false;
    if (tam = 0) then
        achou:= false
    else
    begin
        i:= 1;
        while ((not achou) and (i <= tam)) do 
        begin
            if v[i] = num then
                achou:= true;
            i:= i + 1;
        end;
        if achou then
        begin
            for i:= i - 1 to tam - 1 do    
                v[i]:= v[i + 1];        
            tam:= tam - 1;
        end;
    end;
end;

procedure printar(var v: vetor; tam: integer);
var
    i, j: integer;
    aux: real;
begin
    for j:= 1 to tam  do
        for i:= 2 to tam do
        begin              
            if v[i] < v[i - 1] then
            begin
                aux:= v[i];
                v[i]:= v[i - 1];
                v[i - 1]:= aux;
            end;
        end;
    for i:= 1 to tam do
        write(v[i]:0:1, ' ');
end;

begin
    tam:= 0;
    read(valor);
    while valor <> 0 do
    begin
        read(num);
        achou:= false;
        if (valor = 1) then
        begin
            if tam = 200 then
                writeln('erro')
            else
            begin
                inserir(tam, v, num);
                printar(v, tam);
                writeln;
            end;
        end
        else if (valor = 2) then
        begin
            remover(v, tam, achou, num);
            if not achou then   
                writeln('erro')
            else
            begin
                printar(v, tam);
                writeln;
            end;
        end;
        read(valor);
    end;
    if (tam = 0) then
    begin
        writeln('vazio');
        writeln('vazio');
    end
    else
        printar(v, tam);
end.
