#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "fila.h"
#include "conjunto.h"

// coordenadas para localização do mundo
struct coord {
    int x;
    int y;  
};

// struct contendo a distancia de uma base ate uma missao, 
// e o id da base correspondente.
struct distancia {
    int dist;
    int id_base;
};

// definições dos heróis:
// id do heroi;
// status (vida);
// paciencia;
// velocidade;
// experiencia;
// base em que esta localizado.
typedef struct heroi {
    int id;
    int status; 
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int xp;
    int baseatual;
} H;

// definições da base:
// id da base;
// numero maximo de herois;
// o maximo da fila de espera;
// o conjunto de herois presentes;
// o conjunto das habilidades dos herois presentes;
// a fila de espera;
// as coordenadas.
typedef struct base {
    int id; 
    int lotacao; 
    int qtd_m; 
    int max_fila; 
    struct cjto_t *presenca; 
    struct cjto_t *habilidades; 
    struct fila_t *espera;
    struct coord local;
} B;

// definições das missões:
// id da missao;
// quantidade de tentativas da missao;
// conjunton de habilidades requeridas pela missao;
// coordenadas
typedef struct missao {
    int id;
    int tentativa;
    struct cjto_t *habilidades;
    struct coord local;
} M;

// definicoes gerais da struct mundo:
// compostos v disponiveis;
// habilidades disponiveis;
// herois disponíveis;
// bases disponíveis;
// missoes disponiveis;
// quantidade de eventos completos;
// quantidade de missoes completas;
// qual a tentativa maxima por missao;
// qual a tentativa minima por missao;
// soma das tentativas por missao;
// vetor representando os herois;
// vetor representando as bases;
// vetor representando as missoes.
// tempo atual do mundo;
// vetor representando as distancias;
// dimensoes do mundo.
typedef struct world {
    int qtd_compstv; 
    int qtd_hab;    
    int qtd_H; 
    int qtd_B; 
    int qtd_M;
    int qtd_ev; 
    int qtd_mi;
    int qtd_morte;
    int max_tent;
    int min_tent;
    int soma_tent;
    H *vet_H;
    B *vet_B; 
    M *vet_M; 
    int clk;
    struct distancia *vet_dist;
    struct coord local;
} W;

#endif