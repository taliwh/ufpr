#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdio.h>
#include <stdint.h>

#define T 2

/*
  struct que armazena:
  quantidade de chaves;
  vetor com as chaves;
  vetor com os filhos;
  booleano que indica se é folha;
  booleano que indica se o nodo possui o maximo de chaves (2t - 1).
*/
struct nodo
{
  int32_t qtd_chav;
  int32_t chaves[2 * T - 1];
  struct nodo* filhos[2 * T];
  bool eh_folha;
  bool eh_cheio;
};

struct arvoreB
{
  struct nodo* raiz;
  int32_t t_arvore;
};

struct arvoreB* criarArvoreB(int32_t t_arvore);
void inserirArvoreB(struct arvoreB* arvore, int32_t chave);
void imprimirArvoreB(struct arvoreB* arvore);
void imprimirEmOrdem(struct arvoreB* arvore);
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                           int32_t* idxEncontrado);
void deletarArvore(struct arvoreB* arvore);

// funcoes auxiliares
struct nodo* divideRaiz(struct arvoreB*);
void divideFilho(struct arvoreB*, struct nodo* pai, int32_t i);
void imprimirNodo(struct nodo* no);
void imprimeOrdenado(struct nodo* no);
void inserirNaoCheio(struct arvoreB* arvore, struct nodo* no, int32_t chave);

#endif
