/* arquivo de testes */

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
  inserirArvoreB(arv, 3);
  inserirArvoreB(arv, 5);
  inserirArvoreB(arv, 2);
  imprimirArvoreB(arv);

  printf("\n");
  
  /* Divide a raiz, e arvore aumenta um nivel */
  inserirArvoreB(arv, 1);
  imprimirArvoreB(arv);

  printf("\n");
  
  /* Deixa o filho direito da raiz cheio */
  inserirArvoreB(arv, 8);
  inserirArvoreB(arv, 9);
  imprimirArvoreB(arv);

  printf("\n");
  
  /* Divide o filho direito e passa o 10 pra raiz */
  inserirArvoreB(arv, 10);
  imprimirArvoreB(arv);

  printf("\n");

  imprimirEmOrdem(arv);
  printf("\n");

  buscarArvoreB(arv, 2, &id);
  printf("%d\n", id);

  // Liberar memoria da arvore
  deletarArvore(arv);

  return 0;
}