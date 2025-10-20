//O custo ao consumidor de um carro novo é a soma do custo de fábrica com a percentagem do distribuidor e dos impostos (aplicados ao custo de fábrica).
//Supondo que a percentagem do distribuidor seja de 28% e os impostos de 45%, faça um programa Pascal que leia um número inteiro representando o custo de fábrica de um carro e imprima o custo ao consumidor.

//PS: Use somente operadores inteiros.

//Exemplos:
//Entrada 1:
//15000
//Saída Esperada 1:
//25950

//Entrada 2:
//12500
//Saída Esperada 2:
//21625

//Entrada 3:
//8350
//Saída Esperada 3:
//14445

program expressao;
var a: integer;
calculo: real;
begin
     read(a);
     calculo:= (a + ((28 / 100) * a) + ((45 / 100) * a));
     writeln(trunc(calculo));
end.
