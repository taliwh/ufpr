/* trabalho alg 3 thalisia grr20256088 arv bpapapap */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#define T 2
int
main()
{
  if (T > 1073741823 || T < 2)
    {
      fprintf(stderr, "Valor de t invalido.");
      exit(1);
    }

  struct arvoreB* arv = criarArvoreB(T);

  inserirArvoreB(arv, 3);
  inserirArvoreB(arv, 5);
  inserirArvoreB(arv, 2);
  imprimirArvoreB(arv);

  printf("\n");

  inserirArvoreB(arv, 1);
  imprimirArvoreB(arv);

  printf("\n");

  inserirArvoreB(arv, 8);
  inserirArvoreB(arv, 9);
  imprimirArvoreB(arv);

  printf("\n");

  inserirArvoreB(arv, 10);
  imprimirArvoreB(arv);

  printf("\n");

  deletarArvore(arv);

  return 0;
}