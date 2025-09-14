//Sabe-se que para iluminar de maneira correta os cômodos de uma casa, para cada Metro quadrado (m2) deve-se usar 18W de potência.
//Faça um programa Pascal que:

//receba dois inteiros representando as duas dimensões de um comodo em metros;
//calcule e imprima a sua área em m2;
//imprima a potência de iluminação que deverá ser usada em watts.

//Exemplos:
//Entrada 1:
//10 10
//Saída Esperada 1:
//100 1800

//Entrada 2:
//5 7
//Saída Esperada 2:
//35 630

program iluminar;
var a, b, area, potencia: integer;
begin
      read(a);
      read(b);
      area:= (a * b);
      potencia:= (area * 18);
      writeln(area, ' ', potencia);
end.
