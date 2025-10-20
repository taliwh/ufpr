(* Faça um programa Pascal que leia um número d que é um dígito entre 0 e 9 e depois leia um outro inteiro n qualquer. Em seguida conte quantos dígitos d existem em n. Se não existir nenhum dígito correspondente, a mensagem "NAO" deve ser impressa. Caso contrário imprima o resultado do seu cálculo.

Exemplos:
Entrada 1:
9
95949
Saída Esperada 1:
3

Entrada 2:
1
2353
Saída Esperada 2:
NAO *)

program digitos;
var
    digito, valor, proxvalor, alg, qtd: longint;
begin
    read(digito);
    read(valor);
    qtd:= 0;
    while valor <> 0 do                   
    begin
        alg:= valor mod 10;       
        if (alg = digito) then
            qtd:= qtd + 1;
        proxvalor:= valor div 10;
        valor:= proxvalor;
    end;
    if (qtd > 0) then
        writeln(qtd)
    else
        writeln('NAO');
end.


