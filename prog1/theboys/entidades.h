#ifndef ENTIDADES
#define ENTIDADES_EVENTOS

#include "fila.h"
#include "conjunto.h"

// coordenadas para localização do mundo
typedef struct coord {
    int x;
    int y;
} coord;

// definições dos heróis
typedef struct heroi {
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int xp;
    int baseatual;
} H;

// definições da base
typedef struct base {
    int id; // identificacao da base
    int lotacao; // numero maximo de herois 
    struct cjto_t *presenca; //conjunto de herois 
    coord local;
} B;

//definições das missões
typedef struct missao {
    int id;
    struct cjto_t *habilidades;
    coord local;
} M;


/* DEFINICOES DO MUNDO, RESPECTIVAS QUANTIDADES:
 *
 * habilidades disponiveis;
 * compostos v disponiveis;
 * herois disponíveis;
 * bases disponíveis;
 * missoes disponiveis;
 * vetor representando os herois
 * vetor representando as bases
 * vetor representando as missoes
 * tamanho do mundo
 * tempo atual do mundo
*/
typedef struct world {
    int hab; 
    int compstv; 
    int qtd_H; 
    int qtd_B; 
    int qtd_M
    int *vet_H;
    int *vet_B; 
    int *vet_M; 
    coord local; 
    int clk; 
} W;

#endif