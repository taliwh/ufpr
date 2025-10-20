//Faça um programa Pascal que leia do teclado dois valores inteiros x e y, e em seguida calcule e imprima o valor da seguinte expressão:

//x ao cubo + xy

//Exemplos:
//Entrada 1:
//4 3
//Saída Esperada 1:
//76

//Entrada 2:
//5 2
//Saída Esperada 2:
//135

program expressao;
var a, b, calculo: integer;
begin
     read(a);
     read(b);
     calculo:= ((a * a * a) + (a * b));
     writeln(calculo);
end.
