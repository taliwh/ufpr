#include <stdlib.h>
#include <stdio.h>
#include "arvoreB.h"
#include "fila.h"

struct nodo_fila
{
  struct nodo* nodo_arvore;
  struct nodo_fila* prox;
};

struct fila
{
  struct nodo_fila* ini;
  struct nodo_fila* ptr; /* ponteiro para algum nodo_fila da fila (iterador) */
  int32_t tamanho;
};

/* cria uma fila inicial alocada de tamanho nulo */
struct fila*
fila_cria()
{
  struct fila* fila;

  fila = malloc(sizeof(struct fila));

  if (!(fila))
    return NULL;

  fila->ini = NULL;
  fila->ptr = NULL;
  fila->tamanho = 0;

  return fila;
}

/*
 * desaloca todas as memorias e os ponteiros correspondentes recebem NULL;
 * com a variavel aux, percorre toda a fila;
 * utiliza-se a variavel aux_prox para nao haver perca de elementos da fila.
 */
void
fila_destroi(struct fila** fila)
{
  struct nodo_fila* aux;
  struct nodo_fila* aux_prox;

  aux = (*fila)->ini;

  while (aux != NULL)
    {
      aux_prox = aux->prox;
      free(aux);
      aux = aux_prox;
    }

  free(*fila);
  *fila = NULL;
}

/* insere um novo nodo_fila alocado com a chave escolhida no começo da fila */
int32_t
fila_insere_inicio(struct fila* fila, struct nodo* nodoarv)
{
  struct nodo_fila* novo;

  novo = malloc(sizeof(struct nodo_fila));

  if (!(novo))
    return 0;

  novo->nodo_arvore = nodoarv;
  novo->prox = fila->ini;
  fila->ini = novo;
  fila->tamanho++;

  return 1;
}

/*
 * insere um novo nodo_fila alocado no final da fila;
 * se a fila for vazia, é preferível inserir a chave com a função
 * insere_inicio, pois não terá elementos antecessores; insere sem perca de
 * elementos da fila, e atualiza o seu tamanho.
 */
int32_t
fila_insere_fim(struct fila* fila, int32_t chave)
{
  struct nodo_fila* novo;
  struct nodo_fila* aux;

  if (fila_vazia(fila))
    return fila_insere_inicio(fila, chave);

  novo = malloc(sizeof(struct nodo_fila));

  if (!(novo))
    return 0;

  aux = fila->ini;

  while (aux->prox != NULL)
    aux = aux->prox;

  novo->chave = chave;
  novo->prox = NULL;
  aux->prox = novo;
  fila->tamanho++;

  return 1;
}

/* indica se a fila está sem elementos */
int32_t
fila_vazia(struct fila* fila)
{
  if (!(fila->ini))
    return 1;

  return 0;
}

/*
 * remove o primeiro elemento e indica a chave que foi retirada;
 * verifica se a fila esta vazia;
 * o ultimo elemento recebe free e o tamanho da fila eh atualizado.
 */
int32_t
fila_remove_inicio(struct fila* fila, int32_t* chave)
{
  struct nodo_fila* aux;

  if (fila_vazia(fila))
    return 0;

  aux = fila->ini;
  fila->ini = fila->ini->prox;
  *chave = aux->chave;
  free(aux);
  fila->tamanho--;

  return 1;
}

/* retorna quantidade de elementos da fila */
int32_t
fila_tamanho(struct fila* fila)
{
  return fila->tamanho;
}

/* inicia o iterador */
void
fila_inicia_iterador(struct fila* fila)
{
  fila->ptr = fila->ini;
}

/* move a posicao do iterador e declara qual chave está sendo apontada */
int32_t
fila_incrementa_iterador(struct fila* fila, int32_t* chave)
{
  if (!(fila->ptr))
    return 0;

  *chave = fila->ptr->chave;
  fila->ptr = fila->ptr->prox;

  return 1;
}
