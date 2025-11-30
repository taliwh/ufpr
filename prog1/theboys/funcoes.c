#include "funcoes.h"

//funcoes auxiliares usadas pelo eventos.c 
int aleat (int min, int max) {
    int aleat;

    aleat = min + rand () % (max - min + 1);

    return aleat;
}

int distancia_bases(int x1, int x2, int y1, int y2) {
    int dx, dy;

    dx = x2 - x1;
    dy = y2 - y1;

    return hypot(dx, dy);
}

struct distancia *intercala(struct distancia *vetor, int a, int meio, int b) {
    int i, j;
    struct distancia *u;

    i = a;
    j = meio + 1;

    u = malloc((b - a + 1) * sizeof(struct distancia));
    
    if (!u) 
        return vetor;

    if (a >= b)
        return vetor;

    for (int k = 0; k <= b - a; k++) 
        if (j > b || (i <= meio && vetor[i].dist <= vetor[j].dist)) {
            u[k] = vetor[i];
            i++;
        }
        else {
            u[k] = vetor[j];
            j++;
        }

    for (int k = 0; k <= (b - a); k++) {
        vetor[a + k] = u[k];
    }

    free(u);

    return vetor;
}


struct distancia *merge_sort(struct distancia *vetor, int ini, int fim) {
    int meio;

    if (ini >= fim)
        return vetor;

    meio = (ini + fim) / 2;
    merge_sort(vetor, ini, meio);
    merge_sort(vetor, meio + 1, fim);

    return intercala(vetor, ini, meio, fim);
}   

void incrementa_xp(W *mundo, int idbase) {
    if (!mundo)
        return;

    for(int h = 0; h < QTD_H_W(mundo); h++) {
        if (cjto_pertence(PRESENCA_B(mundo, idbase), h) == 1 && HEROI_W(mundo, h).status)
            HEROI_W(mundo, h).xp++;
    }
}

int acha_experiente(W *mundo, int idbase) {
    int maior, idheroi;

    if (!mundo)
        return -1;

    maior = -1;
    idheroi = -1;

    for(int h = 0; h < QTD_H_W(mundo); h++) 
        if (cjto_pertence(PRESENCA_B(mundo, idbase), h)) 
            if (XP_H(mundo, h) > maior) {
                maior = XP_H(mundo, h);
                idheroi = h;
            }
        
    return idheroi;
}

struct cjto_t *habilidades_base (W *mundo, int idbase)  {
    struct cjto_t *cjto_hab, *aux;

    cjto_hab = cjto_cria(QTD_HAB_W(mundo));

    for (int h = 0; h < QTD_H_W(mundo); h++) 
        if (cjto_pertence(PRESENCA_B(mundo, idbase), h)) {
            aux = cjto_hab;
            cjto_hab = cjto_uniao(aux, HABILIDADES_H(mundo, h));
            cjto_destroi(aux);
        }

    return cjto_hab;
}
