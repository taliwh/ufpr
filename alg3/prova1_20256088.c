// arquivo referente a papapapapapapa

#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include "fila.h"

/*
  retorna uma arvoreB alocada juntamente com um nodo
  o nodo presente sera a raiz
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

  arv->raiz = calloc(sizeof(1, struct nodo));

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
divideRaiz(struct arvoreB* arvore)
{

  struct nodo* nova_raiz = malloc(sizeof(struct nodo));
  if (!nova_raiz)
    {
      fprintf(stderr, "Falha ao alocar memoria.");
      exit(1);
    }

  nova_raiz->eh_folha = false;
  nova_raiz->eh_cheio = false;
  nova_raiz->qtd_chav = 0;
  nova_raiz->filhos[0] = arvore->raiz;

  arvore->raiz = nova_raiz;
  divideFilho(arvore->raiz, 0);

  return nova_raiz;
}

void
divideFilho(struct arvoreB* arvore, struct nodo* pai, int32_t i)
{
  struct nodo* novo_nodo = calloc(1, sizeof(struct nodo));
  if (!novo_nodo)
    {
      fprintf(stderr, "Falha ao alocar memoria.");
      exit(1);
    }

  int32_t t = arvore->t_arvore;
  struct nodo* nodao = pai->filhos[i];

  novo_nodo->eh_folha = nodao->eh_folha;
  novo_nodo->qtd_chav = t - 1;

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
    }
  else
    {
      /* procura a posicao q a chave se encontra para achar o filho
       * correpsondente p encaixa*/
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

      inserirNaoCheio(no->filhos[i], chave);
    }
}

void
inserirArvoreB(struct arvoreB* arvore, int32_t chave)
{
  if (!arvore || !arvore->raiz)
    {
      fprint(stderr, "Ponteiro nulo recebido.");
      return NULL;
    }

  if (arvore->raiz->eh_cheio)
    {
      struct nodo* nova_raiz = divideRaiz(arvore);
      inserirNaoCheio(nova_raiz, chave);
    }
  else
    {
      inserirNaoCheio(arvore->raiz, chave);
    }
}

void
imprimirArvoreB(struct arvoreB* arvore)
{
  if (!arvore || !arvore->raiz)
    {
      fprintf(stderr, "Ponteiro nulo recebido.");
      return NULL;
    }
  
  int32_t qtd_chav = arvore->raiz->chaves

  struct fila* f = fila_cria();
  for (int32_t i = 0; i < qtd_chav - 1; i++)
    {
      fila_insere_inicio(f, arvore->raiz->chaves[i]);
    }

  while (!fila_vazia(fila))
    {
      for (int32_t i = 0; i < qtd_chav) 
        {

        }
      for (int32_t i = 0 )
      qtd_chav = 
    }
  arvore->raiz
}

void
imprimirEmOrdem(struct arvoreB* arvore)
{
}

struct nodo* // busca binaria inspirado slide vignatti a b vetor etc ,
             // facilitar o custo de cpu.
buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado)
{
  if (!arvore || !arvore->raiz)
    {
      *idxEncontrado = -1;
      fprintf(stderr, "Ponteiro nulo recebido.");
      return NULL;
    }

  int32_t a;
  int32_t b;
  int32_t meio;
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
              return arvore->raiz;
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

void // ver se da pra deletar arvore no estilo pos ordem q nem na arvore
     // binaria
deletarArvore(struct arvoreB* arvore)
{
  if (!arvore->raiz)
    {
      fprintf("Ponteiro nulo recebido.");
      return NULL;
    }
}
