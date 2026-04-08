/*
 * prova1_20256088
 * Trabalho de alg3 feito por: Thalisia
 * Estilo GNU
 * Implementacao de operacoes numa arvoreb
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "arvoreB.h"
#include "fila.h"

/*
 * Aloca uma arvore b e sua respectiva raiz
 * Caso nao haja memoria o suficiente, termina o programa
 */
struct arvoreB*
criarArvoreB(int32_t t_arvore)
{
  struct arvoreB* arv = malloc(sizeof(struct arvoreB));
  if (!arv)
    {
      fprintf(stderr, "Falha ao alocar memoria.");
      exit(1);
    }

  arv->raiz = alocarNodo(t_arvore);

  if (!arv->raiz)
    {
      fprintf(stderr, "Falha ao alocar memoria.");
      free(arv);
      exit(1);
    }

  arv->t_arvore = t_arvore;
  arv->raiz->eh_folha = true;

  return arv;
}

struct nodo*
alocarNodo(int32_t t_arvore)
{
  struct nodo* no = calloc(1, sizeof(struct nodo));
  if (!no)
    {
      return NULL;
    }

  no->chaves = calloc(2 * t_arvore - 1, sizeof(int32_t));
  if (!no->chaves)
    {
      free(no);
      return NULL;
    }

  no->filhos = calloc(2 * t_arvore, sizeof(struct nodo*));
  if (!no->filhos)
    {
      free(no->chaves);
      free(no);
      return NULL;
    }

  return no;
}

/*
 * Retorna a nova raiz de uma arvore b, apos ter sido dividida
 * Atualiza o ponteiro da raiz para a nova raiz
 */
struct nodo*
divideRaiz(struct arvoreB* arvore)
{
  struct nodo* nova_raiz = alocarNodo(arvore->t_arvore);
  if (!nova_raiz)
    {
      fprintf(stderr, "Falha ao alocar memoria.");
      exit(1);
    }

  nova_raiz->filhos[0] = arvore->raiz;

  arvore->raiz = nova_raiz;
  divideFilho(arvore, arvore->raiz, 0);

  return nova_raiz;
}
/*
  nodao: nodo cheio
*/
void
divideFilho(struct arvoreB* arvore, struct nodo* pai, int32_t i)
{
  struct nodo* novo_nodo = alocarNodo(arvore->t_arvore);
  if (!novo_nodo)
    {
      fprintf(stderr, "Falha ao alocar memoria.");
      exit(1);
    }

  int32_t t = arvore->t_arvore;
  struct nodo* nodao = pai->filhos[i];

  novo_nodo->eh_folha = nodao->eh_folha;
  novo_nodo->qtd_chav = t - 1;
  novo_nodo->eh_cheio = false;

  /* copia as chaves da segunda metade do nodao para o novo nodo */
  for (int32_t j = 0; j < t - 1; j++)
    {
      novo_nodo->chaves[j] = nodao->chaves[t + j];
    }

  /* copia os filhos das chaves que foram recem copiadas para o novo nodo */
  if (!nodao->eh_folha)
    {
      for (int32_t j = 0; j < t; j++)
        {
          novo_nodo->filhos[j] = nodao->filhos[t + j];
        }
    }

  nodao->qtd_chav = t - 1;
  nodao->eh_cheio = false;

  /* caso o novo nodo tenha q ser inserido no meio de seus irmaos, temos que
     deslocar os filhos do pai para abrir espaco */
  for (int32_t j = pai->qtd_chav; j >= i + 1; j--)
    {
      pai->filhos[j + 1] = pai->filhos[j];
    }

  pai->filhos[i + 1] = novo_nodo;

  /* desloca as chaves para direita para o pai receber a chave mediana */
  for (int32_t j = pai->qtd_chav - 1; j >= i; j--)
    {
      pai->chaves[j + 1] = pai->chaves[j];
    }

  pai->chaves[i] = nodao->chaves[t - 1];
  pai->qtd_chav++;

  /* verifica se pai ficou cheio apos a insercao da chave mediana*/
  if (pai->qtd_chav == 2 * t - 1)
    {
      pai->eh_cheio = true;
    }
}

void
inserirNaoCheio(struct arvoreB* arvore, struct nodo* no, int32_t chave)
{
  int32_t i = no->qtd_chav - 1;

  if (no->eh_folha)
    {
      /* move as chaves para a direita liberando espaco pra nova chave*/
      while (i >= 0 && chave < no->chaves[i])
        {
          no->chaves[i + 1] = no->chaves[i];
          i--;
        }
      no->chaves[i + 1] = chave;
      no->qtd_chav++;

      if (no->qtd_chav == 2 * arvore->t_arvore - 1)
        {
          no->eh_cheio = true;
        }
      else
        {
          no->eh_cheio = false;
        }
    }
  else
    {
      /* procura a posicao q a chave se encontra para achar o filho
       * correspondente p encaixa*/
      while (i >= 0 && chave < no->chaves[i])
        {
          i--;
        }

      i++;

      if (no->filhos[i]->eh_cheio)
        {
          divideFilho(arvore, no, i);
          if (chave > no->chaves[i])
            {
              i++;
            }
        }

      inserirNaoCheio(arvore, no->filhos[i], chave);
    }
}

/* metodo bstcorman
 * Insere uma chave na arvore, desde que a arvore seja valida
 * Se a raiz estiver cheia, divide a raiz com a funcao divideraiz
 * Insere a chave a partir da raiz nao cheia
 */
void
inserirArvoreB(struct arvoreB* arvore, int32_t chave)
{
  if (!arvore || !arvore->raiz)
    {
      return;
    }

  if (arvore->raiz->eh_cheio)
    {
      struct nodo* nova_raiz = divideRaiz(arvore);
      inserirNaoCheio(arvore, nova_raiz, chave);
    }
  else
    {
      inserirNaoCheio(arvore, arvore->raiz, chave);
    }
}

void
imprimirNodo(struct nodo* no)
{
  if (no->eh_folha)
    {
      printf("F");
    }
  else
    {
      printf("I");
    }

  printf(" (n:%d) ", no->qtd_chav);

  printf("[");
  for (int32_t i = 0; i <= no->qtd_chav - 1; i++)
    {
      printf("%d", no->chaves[i]);
      if (i < no->qtd_chav - 1)
        {
          printf(" ");
        }
    }

  printf("]");
}

void
imprimirArvoreB(struct arvoreB* arvore)
{
  if (!arvore || !arvore->raiz)
    {
      return;
    }

  struct fila* f = fila_cria();
  struct nodo* no;
  int32_t n = 0;

  fila_insere_inicio(f, arvore->raiz);
  fila_insere_fim(f, NULL);

  printf("----//----\n");
  printf("Nivel %d\n", n);
  printf("----//----\n");

  while (!fila_vazia(f))
    {
      fila_remove_inicio(f, &no);
      if (no)
        {
          imprimirNodo(no);
          printf("  ");

          if (!no->eh_folha)
            {
              for (int32_t i = 0; i <= no->qtd_chav; i++)
                {
                  fila_insere_fim(f, no->filhos[i]);
                }
            }
        }
      else
        {
          printf("\n");

          if (!fila_vazia(f))
            {
              n++;
              printf("----//----\n");
              printf("Nivel %d\n", n);
              fila_insere_fim(f, NULL);
            }
        }
    }

  fila_destroi(&f);
}

void
imprimeOrdenado(struct nodo* no)
{
  int32_t i;
  for (i = 0; i < no->qtd_chav; i++)
    {
      if (!no->eh_folha)
        {
          imprimeOrdenado(no->filhos[i]);
        }

      printf("%d ", no->chaves[i]);
    }
  if (!no->eh_folha)
    {
      imprimeOrdenado(no->filhos[i]);
    }
}

void
imprimirEmOrdem(struct arvoreB* arvore)
{
  if (!arvore || !arvore->raiz)
    {
      return;
    }

  printf("Em ordem: ");
  if (arvore && arvore->raiz)
    {
      imprimeOrdenado(arvore->raiz);
      printf("\n");
    }
}

/*
 * Realiza uma busca binaria entre os nodos da arvore
 * Percorre um nodo por nivel
 */
struct nodo*
buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado)
{
  if (!arvore || !arvore->raiz)
    {
      *idxEncontrado = -1;
      return NULL;
    }

  int32_t a;
  int32_t b;
  struct nodo* nodo_atual = arvore->raiz;

  while (nodo_atual)
    {
      a = 0;
      b = nodo_atual->qtd_chav - 1;
      while (a <= b)
        {
          int32_t meio = (a + b) / 2;
          if (chave == nodo_atual->chaves[meio])
            {
              *idxEncontrado = meio;
              return nodo_atual;
            }
          if (chave > nodo_atual->chaves[meio])
            {
              a = meio + 1;
            }
          else
            {
              b = meio - 1;
            }
        }
      nodo_atual = nodo_atual->filhos[a];
    }

  *idxEncontrado = -1;
  return NULL;
}

void
deletarNodo(struct nodo* no)
{
  if (!no->eh_folha)
    {
      for (int32_t i = 0; i <= no->qtd_chav; i++)
        {
          deletarNodo(no->filhos[i]);
        }
    }

  free(no->chaves);
  free(no->filhos);
  free(no);
}

void
deletarArvore(struct arvoreB* arvore)
{
  if (!arvore || !arvore->raiz)
    {
      return;
    }

  deletarNodo(arvore->raiz);
  free(arvore);
}
