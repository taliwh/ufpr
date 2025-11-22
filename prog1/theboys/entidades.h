#ifndef ENTIDADES
#define ENTIDADES

#include <fila.h>

typedef struct coord {
    int x;
    int y;
} coord;

typedef struct conjunto {
    int *vet; // vetor 
    int tam; // tamanho alocado 
    int qtd; // quantidade de elementos presentes
} conjunto;

typedef struct H {
    int id;
    conjunto *habilidades;
    int paciencia;
    int velocidade;
    int xp;
    int baseatual;
} H;

typedef struct B {
    int id; // identificacao da base
    int lotacao; // numero maximo de herois 
    conjunto *presenca; //conjunto de herois presentes
    struct fila_t *fila;
    coord local;
} B;

typedef struct M {
    int id;
    conjunto *habilidades;
    coord local;
} M;

// botar oq ta comentado a direita aq em cima soq bontinho
typedef struct W {
    int hab; // quantidade de habilidades possiveis
    int compstv; // numeros de compostos v disponiveis
    int qtd_h; // quantidade de herois presentes
    int qtd_b; // quantidade de bases presentes
    int *vet_h; // vetor com os herois
    int *vet_b; // vetor com as bases
    int *vet_m; // vetor com as missoes
    coord local; // tamanho do mundo
    int clk; // tempo atual do mundo
} W;

#endif