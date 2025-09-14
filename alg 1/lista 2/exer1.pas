Faça um programa Pascal que leia do teclado três valores reais que são as três notas obtidas por uma pessoa. Leia também um valor inteiro que indica a quantidade de faltas dessa pessoa.

Caso o resultado da média aritmética seja inferior a 4.0 o programa deverá imprimir "NAO".
Caso a média seja maior ou igual e 4.0 e inferior a 7.0, imprima "TALVEZ".
Caso a média seja maior ou igual a 7.0 imprima "SIM".
Alunos com o número de faltas maior ou igual a 10 estarão automaticamente reprovados. Neste último caso, imprima "NAO".

Exemplos:
Entrada 1:
7.5 8.1 9.3 6

Saída Esperada 1:
SIM

Entrada 2:
10.0 9.0 9.3 10

Saída Esperada 2:
NAO

program expressao;
var nota1, nota2, nota3: real;
faltas: integer;
calculo: real;
begin
     read(nota1);
     read(nota2);
     read(nota3);
     read(faltas);
     calculo:= ((nota1 + nota2 + nota3) / 3);
     if (calculo < 4) or (faltas >= 10) then
     writeln('NAO');
     if (calculo >= 4) and (calculo < 7) and (faltas <= 10) then
     writeln('TALVEZ');
     if (calculo >= 7) and (faltas < 10) then
     writeln('SIM');
end.
