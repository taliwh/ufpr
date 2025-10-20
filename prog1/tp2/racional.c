/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna o denominador do racional */
long denominador_r (struct racional r) {
  return r.den;
}

/* retorna o maximo divisor comum */
long mdc (long a, long b) {
  long maior, menor, resto;

  /* evita-se que o mdc calculado seja 0 e ocorra divisao por zero na funcao simplifica_r */
  if (a == 0) 
    return 1;    

  /* define o maior e menor termo */
  if (a > b) {
    maior = a;
    menor = b;
  }
  else {
    maior = b;
    menor = a;
  }

  /* calcula o resto da divisao do maior pelo menor */
  resto = maior % menor;

  /* continua a divisão até o resto ser zero */

  while (resto != 0) {
    maior = menor;
    menor = resto;
    resto = maior % menor;
  }

  return menor;
}

/* calcula o mmc dos racionais */
long mmc (long a, long b) {
  long mmc;

  mmc = a * b / mdc (a, b);
  
  return mmc;
}

/* simplifica os racionais */
struct racional simplifica_r (struct racional r) {
  long divisor;

  /* divide com mdc */
  if (r.den != 0) { 
    divisor = mdc(r.num, r.den);
    r.num = (r.num / divisor);
    r.den = (r.den / divisor);
  }

  /* ajusta  o sinal do racional */
  if (r.den < 0) {
    r.num = r.num * -1;
    r.den = r.den  * -1;
  } 

  return r;
}

/* cria um racional estruturado */
struct racional cria_r (long numerador, long denominador) {
  struct racional r = {numerador, denominador}; 

  /* simplifica qualquer r criado */
  r = simplifica_r(r);

  return r;
}

/* verifica se o racional eh valido */
int valido_r (struct racional r) {

  /* verifica se o denominador eh igual a 0 */
  if (r.den == 0)
    return 0;

  return 1;
}



/* imprime as fracoes */
void imprime_r (struct racional r) {

  /* diz se o racional eh invalido */
  if (valido_r (r) == 0)
    printf("NaN"); 
  else {
    
    /* ajusta os sinais corretos */
    if (r.den < 0) {
      r.num = r.num * -1;
      r.den = r.den  * -1;
    } 
    
    /* retorna o resultante da divisao do numerador pelo denominador */
    if (r.num == r.den) {
      printf("%d", 1);
    }
    else if (r.num == 0)
      printf("%d", 0);
    else if (r.den == 1)
      printf("%ld", r.num);

    /* retorna o racional */
    else
      printf("%ld/%ld", r.num, r.den);
  }
}

/* compara o tamanho de dois racionais*/
int compara_r (struct racional r1, struct racional r2) {
  long num1, num2; 

  /* verifica se algum dos racionais sao invalidos */
  if (!(valido_r (r1)) || !(valido_r (r2)))
    return -2;


  /* faz multiplicacao cruzada para comparar */
  num1 = r1.num * r2.den;
  num2 = r2.num * r1.den;
  
  if (num2 == num1)
    return 0;

  if (num2 > num1)
    return -1;
  
  /* caso contrario dos desvios anteriores */
  return 1;
}

/* soma as fracoes */
int soma_r (struct racional r1, struct racional r2, struct racional *r3) {
  long novoden, num1, num2, novonum;

  /* verifica se alguma racional eh invalido ou se r3 eh nulo*/
  if (!(valido_r (r1)) || !(valido_r (r2)) || r3 == NULL)
    return 0;

  /* encontra os numeradores equivalentes conforme o mmc encontrado e realiza a soma entre eles */
  novoden = mmc(r1.den, r2.den);
  num1 = (novoden / r1.den) * r1.num;
  num2 = (novoden / r2.den) * r2.num;
  novonum = num1 + num2;

  /* atualiza o ponteiro r3 com o valor da soma*/
  r3 -> num = novonum;
  r3 -> den = novoden;

  /* simplifica o resultado */
  *r3 = simplifica_r(*r3);

  return 1;
}

