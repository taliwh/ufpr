//Faça um programa que leia um número inteiro n (0 <= n <= 200) e em seguida leia uma sequência de n valores reais e os insira em um vetor de reais.
//O programa deve imprimir na saída o resultado da divisão da soma dos valores positivos que estão em posições pares pela soma dos valores
//negativos que estão nas posições ímpares. Cuidado com divisões por zero.
program estudo;
type
	vetor = Array[1..200] of real;
var
	v: vetor;
	divisao, somapos, somaneg, valor: real;
	tam, i: integer;"C:\Users\User\Desktop"
	
begin
	read(tam);
	somapos:= 0;
	somaneg:= 0;
	if (tam = 0) then
	writeln('vetor vazio')
	else
	begin
	  for i:= 1 to tam do
	    begin
	        read(valor);
	        v[i]:= valor;
	        if ((i mod 2) <> 0) and (v[i] < 0) then
	            somaneg:= v[i] + somaneg;
	        if ((i mod 2) = 0) and (v[i] > 0) then
	            somapos:= v[i] + somapos;
	    end;
	
	    if (somaneg = 0) then
	        writeln('divisao por zero')
	    else
	    begin
	        divisao:= somapos / somaneg;
	        writeln(divisao:0:2);
	    end;
	end;
end.
