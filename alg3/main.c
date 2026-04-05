/* Arquivo de testes */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#define T 2

int
main()
{
  int32_t id;

  /* Verifica se o valor de T eh valido */
  if (T > 1073741823 || T < 2)
    {
      fprintf(stderr, "Valor de t invalido.");
      exit(1);
    }

  struct arvoreB* arv = criarArvoreB(T);

  /* Deixa a raiz cheia */
  inserirArvoreB(arv, 1);
  inserirArvoreB(arv, 2);
  inserirArvoreB(arv, 3);
  imprimirArvoreB(arv);

  printf("\n");

  /* Divide a raiz, e arvore aumenta um nivel */
  inserirArvoreB(arv, 4);
  imprimirArvoreB(arv);

  printf("\n");

  /* Deixa o filho direito da raiz cheio */
  inserirArvoreB(arv, 5);
  imprimirArvoreB(arv);

  printf("\n");

  /* Divide o filho direito e leva mais uma chave para a raiz */
  inserirArvoreB(arv, 6);
  imprimirArvoreB(arv);

  printf("\n");

  /* Imprime todas as chaves da arvore de maneira ordenada */
  imprimirEmOrdem(arv);

  printf("\n");

  /* Busca de uma chave especifica */
  buscarArvoreB(arv, 7, &id);
  if (id == -1)
    {
      printf("Essa chave nao esta presente na arvore.\n");
    }
  else
    {
      printf("O indice em que a chave 9 esta presente eh o: %d\n.", id);
    }

  /* Libera memoria da arvore */
  deletarArvore(arv);

  return 0;
}