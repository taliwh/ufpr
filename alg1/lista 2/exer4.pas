Faça um programa Pascal que leia três números inteiros (P1, P2 e P3) contendo as notas das três provas de um aluno em uma certa disciplina e imprima a média final deste aluno, a qual deve ser um número inteiro. Considerar que a média é ponderada e que o peso das notas é 1, 2 e 3, respectivamente. A fórmula que calcula essa média é:

(p1 + 2p2 + 3p3) / 1 + 2 + 3

Exemplos:
Entrada 1:
10 50 80
Saída Esperada 1:
58

Entrada 2:
90 100 48
Saída Esperada 2:
72

program Hello;
var a, b, c, calculo: integer;
begin
  read(a, b, c);
  calculo:= (a*1 + b*2 + c*3) div 6;
  writeln (calculo);
end.
