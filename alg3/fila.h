#ifndef _fila_t_H
#define _fila_t_H

struct nodo_fila;
struct fila;
struct fila* fila_cria();
void fila_destroi(struct fila** fila);
int32_t fila_insere_inicio(struct fila* fila, struct nodo* nodoarv);
int32_t fila_insere_fim(struct fila* fila, struct nodo* nodoarv);
int32_t fila_remove_inicio(struct fila* fila, struct nodo** nodoarv);
int32_t fila_vazia(struct fila* fila);
int32_t fila_tamanho(struct fila* fila);
void fila_inicia_iterador(struct fila* fila);
int32_t fila_incrementa_iterador(struct fila* fila, struct nodo** nodoarv);

#endif
