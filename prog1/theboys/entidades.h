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
    struct cjto_t *presenca; //conjunto de herois presentes
    struct coord local;
    struct fila_t *espera;
} B;

//definições das missões
typedef struct missao {
    int id;
    int tentativas;
    struct cjto_t *habilidades;
    struct coord local;
} M;

// struct estatisticas {
//     int missoes;
//     int eventos;
//     int mortes;

// };

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
    int compstv; 
    int hab;    
    int qtd_H; 
    int qtd_B; 
    int qtd_M;
    int clk;
    H *vet_H;
    B *vet_B; 
    M *vet_M; 
    // struct estatistica dados;
    struct coord local;
} W;

#endif