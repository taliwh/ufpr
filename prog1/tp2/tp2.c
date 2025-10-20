/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* insere racionais lidos do usuario no vetor */
void le_vetor(struct racional v[], int tam) {
  long num, den;

  /* laco para armazenar todos os valores */
  for(int i = 0; i <= tam - 1; i++) {
    scanf("%ld%ld", &num, &den);

    /* cria os racionais de maneira estruturada e os armazena no vetor */
    v[i] = cria_r(num, den);
  }
}

/* remove racionais invalidos do vetor */
void remove_invalidos(struct racional v[], int *tam) {

  /* laco que percorre o vetor em busca de elementos invalidos */
  for(int i = 0; i <= *tam - 1; i++) {
    if (denominador_r(v[i]) == 0) {

      /* desloca elementos à direita para a esquerda, sobrescrevendo o valor inválido */
      for (int j = i; j < *tam - 1; j++) 
        v[j] = v[j + 1];

      /* atualiza o tamanho do vetor e ajusta índice para não pular elemento após remoção consecutiva */
      (*tam)--;
      i--;
    }
  }
}

/* imprime o vetor de forma organizada utilizando imprime_r*/
void printa_vetor (struct racional v[], int tam) {
  printf("VETOR = ");

  /* apenas imprime se houver elementos */
  if (tam > 0) {
    for(int i = 0; i < tam - 1; i++) {
      imprime_r(v[i]);             
      printf(" ");
    }
      imprime_r(v[tam - 1]);
  }
  printf("\n");
}

/* ordena os elementos do vetor com bubble sort */
void ordena_r (struct racional v[], int tam) {
  struct racional aux;

  /* compara elementos adjacentes e realiza trocas se necessário */
  for (int j = 0; j < tam - 1; j++) 
    for (int i = 0; i < tam - 1 - j; i++)  
      if (compara_r (v[i], v[i + 1]) == 1) {
        aux = v[i];
        v[i] = v[i + 1];
        v[i + 1] = aux;
      }
}

/* realiza a somatoria dos racionais do vetor atraves de agrupamento */
void somatotal (struct racional v[], struct racional *somatoria, int tam) {
  struct racional soma;
  int i;
  i = 0;

  /* se o vetor tem tamanho ímpar, processa pares e soma o termo restante */
  if (tam % 2 != 0) {
    while (i != tam - 1) {
      soma_r(v[i], v[i + 1], &soma);
      soma_r(*somatoria, soma, somatoria);
      i = i + 2;
    }

    /* soma o ultimo termo restante */
    soma_r(*somatoria, v[tam - 1], somatoria);
  }

  /* se o tam for par, devemos somar somente os pares */
  else
    while (i < tam - 1) {
      soma_r(v[i], v[i + 1], &soma);
      soma_r(*somatoria, soma, somatoria);
      i = i + 2;
    }
}

/* programa principal */
int main () {
  int tam;
  struct racional v[100];
  struct racional somatoria = {0,1};

  /* le quantidade de elementos do vetor*/
  scanf("%d", &tam);

  /* verifica se o valor lido esta fora do intervalo */
  if (tam <= 0 || tam >= 100)
    return 1;

  /* inclui os racionais lidos no vetor */
  le_vetor(v, tam);
  
  /* imprime vetor */
  printa_vetor(v, tam);

  /* remove as mensagens NaN e imprime o vetor*/
  remove_invalidos(v, &tam);
  printa_vetor(v, tam);

  /* ordena e imprime o vetor*/
  ordena_r(v, tam);
  printa_vetor(v, tam);

  /* calcula e imprime a somatoria dos racionais do vetor*/
  if (tam == 0)
    printf("SOMA = %d", 0);
  else {
    somatotal(v, &somatoria, tam);
    printf("SOMA = ");
    imprime_r(somatoria);
  }
  printf("\n");

  return (0) ;
}