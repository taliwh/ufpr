//Faça um programa Pascal que leia um número real representando o diâmetro (em metros) de uma esfera. Calcule e imprima o volume desta esfera, com duas casas de precisão.
//Lembre-se que o volume de uma esfera é dado pela fórmula:

//v= 4pi/3 * R ao cubo

//Use pi = 3.14.

//Exemplos:
//Entrada 1:
//3
//Saída Esperada 1:
//14.13
//Entrada 2:
//10
//Saída Esperada 2:
//523.33

program esfera;
var volume, diametro, raio: real;
begin
     read(diametro);
     raio:= (diametro / 2);
     writeln(((raio * raio * raio * 4 * 3.14) / 3):0:2);
end.
