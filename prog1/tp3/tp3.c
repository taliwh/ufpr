/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* 
 * insere os racionais no vetor com o laco;
 * armazena os valores com a funcao cria_r.
*/
void le_vetor(struct racional **v, int tam) {
  long num, den;
  for(int i = 0; i <= tam - 1; i++) {
    scanf("%ld%ld", &num, &den);
    v[i] = cria_r(num, den);
  }
}

/* 
 * a funcao remove racionais invalidos do vetor;
 * depois de achar o numero invalido, deixa seu elemento para o final do vetor;
 * destroi a alocacao do numero invalido;
 * atualiza o tamanho do vetor.
*/
void remove_invalidos(struct racional **v, int *tam) {
struct racional *aux;
  for(int i = 0; i <= *tam - 1; i++) {
    if (!(valido_r(v[i]))) {
      aux = v[*tam - 1];
      v[*tam - 1] = v[i];
      v[i] = aux;
      destroi_r(&v[*tam - 1]);
      (*tam)--;
      i--;
    }
  }
}

/* 
 * imprime o vetor de forma organizada utilizando imprime_r; 
 * apenas imprime se houver elementos presentes;
 * imprime sem espaço no último elemento.
*/
void printa_vetor (struct racional **v, int tam) {
  fprintf(stderr, "VETOR = ");
  if (tam > 0) {
    for(int i = 0; i < tam - 1; i++) {
      imprime_r(v[i]);             
      fprintf(stderr, " ");
    }
      imprime_r(v[tam - 1]);
  }
  fprintf(stderr, "\n");
}

/* 
 * ordena os elementos do vetor com bubble sort; 
 * compara elementos adjacentes;
 * realiza trocas se necessario;
 * guarda valor anterior na variavel auxiliar para o valor nao ser perdido.
*/
void ordena_r (struct racional  **v, int tam) {
  struct racional *aux;
  for (int j = 0; j < tam - 1; j++) 
    for (int i = 0; i < tam - 1 - j; i++)  
      if (compara_r (v[i], v[i + 1]) == 1) {
        aux = v[i];
        v[i] = v[i + 1];
        v[i + 1] = aux;
      }
}

/* soma todos os racionais do vetor acumulando em somatoria. */
void somatotal (struct racional **v, struct racional *somatoria, int tam) {
  for(int i = 0; i <= tam - 1; i++)
    soma_r(somatoria, v[i], somatoria);
}

/* devolve a memoria e ponteiro recebe null. */
void libera_r(struct racional **v, int tam) {
  for (int i = 0; i <= tam - 1; i++)
    if (v[i] != NULL)
      destroi_r(&v[i]);
} 

/* programa principal. */
int main () {
  struct racional *somatoria;
  struct racional **v;
  int tam;

  /* le o tamanho e verifica se esta fora do intervalo. */
  scanf("%d\n", &tam);
  if (tam <= 0 || tam >= 100)
    return 1;

  /* aloca espaco na memoria e verifica se deu para alocar. */
  v = malloc(sizeof (struct racional*) * tam);
  if (!v)
    return 1;

  le_vetor(v, tam);

  printa_vetor(v, tam);

  remove_invalidos(v, &tam);

  printa_vetor(v,tam);

  ordena_r(v, tam);

  printa_vetor(v, tam);

  /* atribui uma variavel nula para efeitos de acumulacao da soma a seguir. */
  somatoria = cria_r(0,1);

  /* calcula e imprime a somatoria dos racionais do vetor. */
  if (tam == 0)
    fprintf(stderr, "SOMA = %d", 0);
  else {
    somatotal(v, somatoria, tam);
    fprintf(stderr, "SOMA = ");
    imprime_r(somatoria);
  }
  fprintf(stderr,"\n");

  libera_r(v, tam);

  printa_vetor(v, tam);

  /* libera os ponteiros restantes. */
  free (v);
  free (somatoria);

  return 0;
}