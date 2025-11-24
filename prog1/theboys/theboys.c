// programa principal do projeto "The Boys - 2024/2"
// Autor: Thalísia Arianna Fernandes Fleck, GRR 20256088

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "entidades.h"

// seus #defines vão aqui
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)




// programa principal
int main () {
    srand(0);

    struct fprio_t *lef = fprio_cria();

    // iniciar o mundo





    // para cada her´oi H:
    // base = n´umero aleat´orio [0...N_BASES-1]
    // tempo = n´umero aleat´orio [0...4320] // 4320 = 60*24*3 = 3 dias
    // criar e inserir na LEF o evento CHEGA (tempo, H, base)

    for h to N_HEROIS












    // executar o laço de simulação

    // executar o laço de simulação

    // destruir o mundo :o

    return 0;
}

