#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "fila.h"
#include "conjunto.h"

// coordenadas para localização do mundo
struct coord {
    int x;
    int y;  
};

// definições dos heróis
typedef struct heroi {
    int id;
    int status; //0 se morto e 1 se vivo
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
    int qtd_m; // qtd de missoes realizadas
    int max_fila; // max da fila de espera
    struct cjto_t *presenca; //conjunto de herois presentes
    struct coord local;
    struct fila_t *espera;
} B;

//definições das missões
typedef struct missao {
    int id;
    int tentativa;
    struct cjto_t *habilidades;
    struct coord local;
} M;

/* DEFINICOES DO MUNDO, RESPECTIVAS VARIAVEIS:
 *
 * habilidades disponiveis;
 * compostos v disponiveis;
 * herois disponíveis;
 * bases disponíveis;
 * missoes disponiveis;
 * tempo atual do mundo;
 * dimensoes do mundo;
 * vetor representando os herois;
 * vetor representando as bases;
 * vetor representando as missoes;
*/
typedef struct world {
    int qtd_compstv; 
    int qtd_hab;    
    int qtd_H; 
    int qtd_B; 
    int qtd_M;
    int qtd_ev; //qtd ev concluido
    int qtd_mi; //qtd missao concliuda
    int qtd_morte;
    int max_tent;
    int min_tent;
    int soma_tent; //qtd de tentativas
    H *vet_H;
    B *vet_B; 
    M *vet_M; 
    int clk;
    // struct estatistica dados;
    struct coord local;
} W;

#endif