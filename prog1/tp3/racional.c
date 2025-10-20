/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* aqui vem a struct racional propriamente dita, nao modifique! */
struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* 
 * retorna o maximo divisor comum pelo metodo de euclides;
 * evita que ele seja 0, retornando 1 caso o numerador seja 0;
 * define o maior e menor termo; 
 * aplica divisoes sucessivas ate o resto ser 0.
*/
long mdc (long a, long b) {
  long maior, menor, resto;

  if (a == 0) 
    return 1;    

  if (a > b) {
    maior = a;
    menor = b;
  }
  else {
    maior = b;
    menor = a;
  }

  resto = maior % menor;

  while (resto != 0) {
    maior = menor;
    menor = resto;
    resto = maior % menor;
  }

  return menor;
}

/* calcula o mmc dos racionais com a formula dada. */
long mmc (long a, long b) {
  long mmc;

  mmc = a * b / mdc (a, b);
  
  return mmc;
}

/* retorna o numerador. */
long numerador_r (struct racional *r) {

  return r -> num;
}

/* retorna o denominador. */
long denominador_r (struct racional *r) {

  return r -> den;
}

/* 
 * verifica se o racional eh valido, ou seja,
 * se o ponteiro nao eh nulo e o denominador eh diferente de 0. 
*/
int valido_r (struct racional *r) {
  if (!(denominador_r(r)) || !r )
    return 0;

  return 1;
}

/* 
 * retorna o racional simplificado com o mdc;
 * retorna 0 se este for invalido ou nulo;
 * ajeita o sinal.
*/
int simplifica_r (struct racional *r) {
  long divisor;

  if (!(valido_r(r)) || numerador_r(r) == 0) 
    return 0;

  divisor = mdc(r -> num, r -> den);
  r -> num = (r -> num / divisor);
  r -> den = (r -> den / divisor);

  if (r -> den < 0) {
    r -> num = r -> num * -1;
    r -> den = r -> den  * -1;
  } 

  return 1;
}

/* 
 * retorna um ponteiro para um racional estruturado e alocado;
 * retorna null se nao conseguiu alocar.
*/
struct racional *cria_r (long numerador, long denominador) {
  struct racional *r;
  
  r = malloc(sizeof(struct racional));

  if (!r)
    return NULL;

  r -> num = numerador;
  r -> den = denominador;

  return r;
}

/* 
  * libera a memoria da heap que foi alocada pelo racional;
  * anula o ponteiro.
*/
void destroi_r (struct racional **r) {
  if (r == NULL || *r == NULL)
    return; 

  free(*r);    
  *r = NULL;   
}

/* 
 * imprime os racionais simplificados;
 * imprime "NULL" se o ponteiro eh nulo, "NaN" se e invalido;
 * retorna o racional estruturado se nao atender as condicoes do racional.h.
*/
void imprime_r (struct racional *r) {
  if (!r)  
    fprintf(stderr, "NULL");

  else if (valido_r(r)) {
    simplifica_r(r);

    if (numerador_r(r) == denominador_r(r)) 
      fprintf(stderr, "%d", 1);

    else if (!(numerador_r(r)))
      fprintf(stderr, "%d", 0);

    else if (denominador_r(r) == 1)
      fprintf(stderr, "%ld", numerador_r(r));

    else
      fprintf(stderr, "%ld/%ld", numerador_r(r), denominador_r(r));
  }
  else
    fprintf(stderr, "NaN"); 
}

/* acha um novo numerador conforme o mmc encontrado. */
long ajusta_r(struct racional *r, long mmc) {
  long novonum;

  novonum = (mmc / r -> den) * r -> num;

  return novonum; 
}

/* 
 * compara o tamanho dos racionais pelo mmc;
 * verifica se sao validos.
*/
int compara_r (struct racional *r1, struct racional *r2) {
  long num1, num2, novoden;

  if (!(valido_r (r1)) || !(valido_r (r2)))
    return -2;

  novoden = mmc (r1 -> den, r2 -> den); 
  num1 = ajusta_r(r1, novoden);
  num2 = ajusta_r(r2, novoden);

  if (num2 == num1)
    return 0;

  if (num2 > num1)
    return -1;
  
  return 1;
}

/* 
 * atribui a soma simplificada dos racionais ao r3 pelo mmc;
 * retorna 0 se algum racional for invalido.
*/
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  long novoden, num1, num2, novonum;

  if (!(valido_r (r1)) || !(valido_r (r2)))
    return 0;

  novoden = mmc(r1 -> den, r2 -> den);
  num1 = ajusta_r(r1, novoden);
  num2 = ajusta_r(r2, novoden);
  novonum = num1 + num2;

  r3 -> num = novonum;
  r3 -> den = novoden;

  simplifica_r(r3);

  return 1;
}

/* 
 * atribui a subtracao simplificada dos racionais ao r3 pelo mmc;
 * retorna 0 se algum racional for invalido.
*/
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  long novoden, num1, num2, novonum;

  if (!(valido_r (r1)) || !(valido_r (r2)))
    return 0;

  novoden = mmc(r1 -> den, r2 -> den);
  num1 = ajusta_r(r1, novoden);
  num2 = ajusta_r(r2, novoden);
  novonum = num1 - num2;

  r3 -> num = novonum;
  r3 -> den = novoden;

  simplifica_r(r3);

  return 1;
}

/* 
 * atribui a multiplicacao simplificada dos racionais ao r3;
 * multiplica numerador e denominador correspondentes;
 * retorna 0 se algum racional for invalido. 
*/
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  long novoden, novonum;

  if (!(valido_r (r1)) || !(valido_r (r2)))
    return 0;

  novonum = r1 -> num * r2 -> num;
  novoden = r1 -> den * r2 -> den;

  r3 -> num = novonum;
  r3 -> den = novoden;

  simplifica_r(r3);

  return 1;
}

/* 
 * atribui a divisao dos racionais ao r3;  
 * inverte r2 temporariamente sem alterar seu valor original;
 * retorna a multiplicacao de r1 e r2 invertido.
*/
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  struct racional temp;

  temp.num = r2 -> den;
  temp.den = r2 -> num;

  return multiplica_r(r1, &temp, r3);
}