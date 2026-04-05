#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdio.h>
#include <stdint.h>

/* Define para o T da arvore */
#define T 2

/*
 * Nodo da arvore, que contem:
 *  qtd_chav: quantidade de chaves;
 *  chaves: vetor com as chaves;
 *  filhos: vetor com os filhos;
 *  eh_folha: booleano que indica se é folha;
 *  eh_cheio: booleano que indica se o nodo possui o maximo de chaves (2t - 1).
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

/* Funcoes auxiliares */
struct nodo* divideRaiz(struct arvoreB*);
void divideFilho(struct arvoreB*, struct nodo* pai, int32_t i);
void imprimirNodo(struct nodo* no);
void imprimeOrdenado(struct nodo* no);
void inserirNaoCheio(struct arvoreB* arvore, struct nodo* no, int32_t chave);

#endif
