// programa principal do projeto "The Boys - 2024/2"
// Autor: Thalísia Arianna Fernandes Fleck, GRR 20256088

// seus #includes vão aqui
#include <stdlib.h>
#include "eventos.h"
#include "iniciarmundo.h"
#include "lef.h"
// seus #defines vão aqui
#include "define.h"

// programa principal
int main () {
    W *mundo;
    struct fprio_t *lef;
    srand(0);

    mundo = cria_mundo();
    lef = fprio_cria();
    inicializacao(mundo);
    eventos_iniciais(mundo, lef);
    comecar_lef(mundo, lef);

    
    // executar o laço de simulação

    // executar o laço de simulação

    // destruir o mundo :o

    return 0;
}

