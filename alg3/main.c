/* 
 * Arquivo de testes para a sequencia de chaves: 1 2 3 4 5 6 
 * Os comentarios valem somente para as instancias especificadas
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"

int
main()
{
  int32_t id;
  int32_t chave;
  int32_t t;

  printf("Digite o valor de t para a arvore\n");
  scanf("%d", &t);
  
  struct arvoreB* arv = criarArvoreB(t);
    
  /* Deixa a raiz cheia */
  inserirArvoreB(arv, 1);
  inserirArvoreB(arv, 2);
  inserirArvoreB(arv, 3);
  imprimirArvoreB(arv);

  printf("\n\n");

  /* Divide a raiz, e arvore aumenta um nivel */
  inserirArvoreB(arv, 4);
  imprimirArvoreB(arv);

  printf("\n\n");

  /* Deixa o filho direito da raiz cheio */
  inserirArvoreB(arv, 5);
  imprimirArvoreB(arv);

  printf("\n\n");

  /* Divide o filho direito e leva mais uma chave para a raiz */
  inserirArvoreB(arv, 6);
  imprimirArvoreB(arv);

  printf("\n\n");

  /* Imprime todas as chaves da arvore de maneira ordenada */
  imprimirEmOrdem(arv);

  printf("\n");

  printf("Digite a chave que gostaria de buscar:\n");
  scanf("%d", &chave);
  printf("\n");

  /* Busca de uma chave especifica */
  buscarArvoreB(arv, chave, &id);
  if (id == -1)
    {
      printf("Essa chave nao esta presente na arvore.\n");
    }
  else
    {
      printf("O indice da chave presente no nodo eh o: %d\n", id);
    }

  /* Libera memoria da arvore */
  deletarArvore(arv);

  return 0;
}