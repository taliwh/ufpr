/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* verifica se a fracao eh valida */
int valido_r (struct racional r) {
  /* verifica se o denominador eh igual a 0 */
  if (r.den == 0)
    return 0;
  return 1;
}

/* retorna um numero aleatorio */
int aleat (long min, long max) {
  long aleat;

  /* limita o numero no intervalo de -max e max */
  aleat = min + rand() % (max - min + 1);

  return aleat;
}

/* retorna o maximo divisor comum */
long mdc (long a, long b)
{
  long maior, menor, resto;

  /* essa verificacao do "if (a == 0)" serve para evitar que o mdc calculado seja 0 e ocorra divisao por zero na funcao simplifica_r */
  if (a == 0) 
    return 1;    
  else {

    /* define o maior e menor termo */
    if (a > b) {
      maior = a;
      menor = b;
    }
    else {
      maior = b;
      menor = a;
    }

    /* calcula o resto da divisao do maior pelo menor*/
    resto = maior % menor;

    /* aqui ele dividira o menor termo pelo resto ate achar o resto = 0 */
    while (resto != 0) {
      maior = menor;
      menor = resto;
      resto = maior % menor;
    }
  }

  return menor;
}

/* retorna a fracao simplificada com o mdc */
struct racional simplifica_r (struct racional r) {
  long divisor;

  /* se o denominador eh 0, nao podemos simplificar, ja que o numero eh invalido */
  if (r.den != 0) { 
    divisor = mdc(r.num, r.den);
    r.num = (r.num / divisor);
    r.den = (r.den / divisor);
  }

  return r;
}

/* cria uma fracao estruturada */
struct racional cria_r(long numerador, long denominador) {
  struct racional r = {numerador, denominador}; 

  /* retorna a fracao criada de forma simplificada */
  return simplifica_r(r);
}

/* retorna uma fracao sorteada */
struct racional sorteia_r (long min, long max) {
  struct racional r;

  /* utiliza a funcao aleat para sorteiar o numerador e o denominador */
  r.num = aleat(min, max); 
  r.den = aleat(min, max);

  return cria_r(r.num, r.den);
}

/* calcula o mmc das fracoes */
long mmc (long a, long b) {
  long mmc;

  /* o mmc é obtido dividindo o produto de a e b pelo mdc, pois o mdc remove os fatores comuns já contados duas vezes no produto. */
  mmc = a * b / mdc (a, b);
  
  return mmc;
}

/* imprime as fracoes */
void imprime_r (struct racional r) {

  /* diz se a fracao eh invalida */
  if (valido_r (r) == 0)
    printf("INVALIDO"); 
  else {

    /* esse if evita com que somente o denominador fique com sinal negativo, passando o sinal para o numerador. tambem faz com que
    uma fracao de numerador e denominador negativo tenha um valor positivo */
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

    /* retorna a fracao */
    else
      printf("%ld/%ld", r.num, r.den);
  }
}

/* retorna a soma das fracoes */
struct racional soma_r (struct racional r1, struct racional r2) {
  long novoden, num1, num2, novonum;

  /* se alguma fração eh invalida, retorna uma fração nula para indicar erro */
  if (valido_r (r1) == 0 || valido_r (r2) == 0)
    return cria_r(0,0);

  /* encontra os numeradores equivalentes conforme o mmc encontrado e realiza a soma entre eles */
  novoden = mmc(r1.den, r2.den);
  num1 = ( novoden / r1.den ) * r1.num;
  num2 = ( novoden / r2.den ) * r2.num;
  novonum = num1 + num2;

  return cria_r(novonum, novoden);
}

/* retorna a subtracao das fracoes */
struct racional subtrai_r (struct racional r1, struct racional r2) {
  long novoden, num1, num2, novonum;

  /* se alguma fração eh invalida, retorna uma fração nula para indicar erro */
  if (valido_r (r1) == 0 || valido_r (r2) == 0)
    return cria_r(0,0);

  /* encontra os numeradores equivalentes conforme o mmc encontrado e realiza a subtracao entre eles */
  novoden = mmc(r1.den, r2.den);
  num1 = ( novoden / r1.den ) * r1.num;
  num2 = ( novoden / r2.den ) * r2.num;
  novonum = num1 - num2;

  return cria_r(novonum, novoden);
}

/* retorna a multiplicacao das fracoes */
struct racional multiplica_r (struct racional r1, struct racional r2) {
  long novoden, novonum;
    
  /* multiplica numeradores e denominadores correspondentes */
  novoden = r1.den * r2.den;
  novonum = r1.num * r2.num;

  return cria_r(novonum, novoden);
}

/* divide as fracoes */
struct racional divide_r (struct racional r1, struct racional r2) {
  long aux;

  /* inverte o numerador e denominador de r2 com o auxilio da variavel aux */
  aux = r2.num;
  r2.num = r2.den;
  r2.den = aux;

  /* multiplica as fracoes */
  return multiplica_r(r1, r2);
} 

