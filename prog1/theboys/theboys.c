// programa principal do projeto "The Boys - 2024/2"
// Autor: Thalísia Arianna Fernandes Fleck, GRR 20256088

// seus #includes vão aqui
#include <stdlib.h>
#include "iniciarmundo.h"
#include "lef.h"

// seus #defines vão aqui
#include "define.h"

// programa principal
int main () {
    W *mundo;
    struct fprio_t *lef;
    srand(0);

    // cria o mundo e a lef
    mundo = cria_mundo();
    lef = fprio_cria();

    // inicializa as structs e eventos
    inicializacao(mundo);
    eventos_iniciais(mundo, lef);

    // comeca a simulacao do mundo
    comecar_lef(mundo, lef);

    // destroi o mundo, acaba a simulacao
    destroi_mundo(mundo);

    return 0;
}

