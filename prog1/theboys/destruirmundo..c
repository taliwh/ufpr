#include "conjunto.h"
#include <stdlib.h> 
#include "entidades.h"

void destroi_mundo(W *mundo) {
    
    for (int h = 0; h < QTD_H_W(mundo); h++) {
        cjto_destroi(HABILIDADES_H(mundo, h));
        free(HEROI_W(mundo, h));
    }
    
    for (int b = 0 ; b < QTD_B_W(mundo) ; b++) {
        cjto_destroi(PRESENCA_B(mundo, b));
        fila_destroi(FILA_ESPERA_B(mundo, b));
        free(BASE_W(mundo, b));
    }

    for (int m = 0 ; QTD_M_W(mundo); m++) {
        cjto_destroi(HABILIDADES_M(mundo, m));
        free(MISSAO_W(mundo, m));
    }
    free(mundo -> vet_B);
    free(mundo -> vet_B);
    free(mundo -> vet_M);       
    free(mundo);
}
