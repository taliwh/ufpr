Faça um programa Pascal que leia um número inteiro e imprima o seu sucessor e seu antecessor, na mesma linha.

Exemplos:
Entrada 1:
1
Saída Esperada 1:
2 0

Entrada 2:
100
Saída Esperada 2:
101 99

program Hello;
var a, sucessor, antecessor: integer;
begin
  read(a);
  sucessor:= (a + 1);
  antecessor:= (a - 1);
  write(sucessor, ' ', antecessor);
end.
