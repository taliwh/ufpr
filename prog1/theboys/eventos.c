#include "eventos.h"

struct evento {
    int tipo;
    int base;
    int baseprox; // so usa com viaja 
    int heroi;
    int tempo;
    int distancia; //so usa com viaja e umas coisas ai
    int missao;
};

int aleat (int min, int max) {
    int aleat;

    aleat = min + rand () % (max - min + 1);

    return aleat;
}

//retorna -1 se erro 
int distancia_bases(int x1, int x2, int y1, int y2) {
    int soma;
    int distancia;

    soma = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    distancia = sqrt(soma);

    return distancia;
}

struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, double distancia, int missao) {
    struct evento *evento_novo;

    evento_novo = malloc(sizeof(struct evento));
    if (!mundo || !evento_novo) {
        printf("falha ao criar evento");
        return NULL;
    }

    evento_novo -> tipo = tipo;
    evento_novo -> heroi = heroi;
    evento_novo -> tempo = tempo;
    evento_novo -> base = base;
    evento_novo -> baseprox = baseprox;
    evento_novo -> missao = missao;
    evento_novo -> distancia = distancia;

    return evento_novo;
}

//o tempoaux pode ser utilizado para verificar se a missoa foi cumprida, 1 significa q sim e 0 significa q nao foi comprida
void printa_evento(W *mundo, struct evento *ev, int aux) {

    if (!mundo || !ev) {
        printf("falha ao printar");   
        return;
    }

    //aumenta a quantidade de eventos
    QTD_E_W(mundo)++;

    switch (ev -> tipo) {
        case TIPO_CHEGA:
            if (aux)
                printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            else
                printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            break;

        case TIPO_ESPERA:
            printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", ev -> tempo, ev -> heroi, ev -> base, QTD_FILA_ESPERA_B(mundo, ev -> base));
            break;

        case TIPO_DESISTE:
            printf("%6d: DESIST HEROI %2d BASE %d\n", ev -> tempo, ev -> heroi, ev -> base);
            break;

        case TIPO_AVISA:
            printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", ev -> tempo, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            fila_imprime(FILA_ESPERA_B(mundo, ev -> base));
            printf(" ]\n");
            printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", ev -> tempo, ev -> base, ev -> heroi);
            break;

        case TIPO_ENTRA:
            printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base), ev -> tempo + aux);
            break;

        case TIPO_SAI:
            printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            break;

        case TIPO_VIAJA:
            printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", ev -> tempo, ev -> heroi, ev -> base, ev -> baseprox, ev -> distancia, VELOCIDADE_H(mundo, ev -> heroi), ev -> tempo + aux);
            break;

        case TIPO_MORRE:
            printf("%6d: MORRE HEROI %2d MISSAO %d\n",  ev -> tempo, ev -> heroi, ev -> missao);
            break;

        case TIPO_FIM:
            printf("FIM\n\n");

            for(int h = 0; h < QTD_H_W(mundo); h++){
                if (STATUS_H(mundo, h)) {
                    printf("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ", h, PACIENCIA_H(mundo, h), VELOCIDADE_H(mundo, h), XP_H(mundo, h));
                    cjto_imprime(HABILIDADES_H(mundo, h));
                    printf(" ]\n");
                }
                else {
                    printf("HEROI %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ", h, PACIENCIA_H(mundo, h), VELOCIDADE_H(mundo, h), XP_H(mundo, h));
                    cjto_imprime(HABILIDADES_H(mundo, h));
                    printf(" ]\n");                   
                }
            }

            for(int b = 0; b < QTD_B_W(mundo); b++) 
                printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", b, LOTACAO_B(mundo, b), MAX_FILA_B(mundo, b), QTD_M_B(mundo, b));

            printf("EVENTOS TRATADOS: %d\n", QTD_E_W(mundo));
            printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", QTD_MI_W(mundo), QTD_M_W(mundo), (QTD_MI_W(mundo) * 100.0) / QTD_M_W(mundo));
            printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", MIN_TENT_M(mundo), MAX_TENT_M(mundo), SOMA_TENT_M(mundo) * 1.0 / QTD_MI_W(mundo));
            printf("TAXA DE MORTALIDADE: %.1f%%\n", (QTD_MORTE_W(mundo) * 100.0) / QTD_H_W(mundo));
            break;

        // printf("\n");
    }
}

void printa_missao (W *mundo, struct evento *ev, struct cjto_t *hab, int tent, int cumprida){
    if (!mundo || !ev)
        return;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [", ev -> tempo, ev -> missao, tent);
    cjto_imprime(HABILIDADES_M(mundo, ev -> missao));
    printf("]\n");

    if (cumprida) {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [", ev -> tempo, ev -> missao, ev -> base);
        cjto_imprime(hab);
        printf("]\n");
    }
    else
        printf("%6d: MISSAO %d IMPOSSIVEL\n", ev -> tempo, ev -> missao);
}


void incrementa_xp(W *mundo, int idbase) {
    if (!mundo)
        return;

    for(int h = 0; h < QTD_H_W(mundo); h++) {
        if (cjto_pertence(PRESENCA_B(mundo, idbase), h) == 1 && HEROI_W(mundo, h).status)
            HEROI_W(mundo, h).xp++;
    }
}

int acha_experiente(W *mundo) {
    int maior;
    int idheroi;

    if (!mundo)
        return -1;

    maior = -1;
    idheroi = 0;

    for(int h = 0; h < QTD_H_W(mundo); h++) {
        if (XP_H(mundo, h) > maior) {
            maior = XP_H(mundo, h);
            idheroi = h;
        }
    }

    return idheroi;
}

void eventos_iniciais (W *mundo, struct fprio_t *lef) {
    struct evento *chega;
    struct evento *missao;
    struct evento *fim;
    int tempo;

    if (!lef || !mundo) {
        printf("falha em realizar eventos iniciais");
        return;
    }

    // para cada heroi:
    for (int h = 0; h < QTD_H_W(mundo); h++) {
        BASEATUAL_H(mundo, h) = aleat(0, QTD_B_W(mundo) -1);
        tempo = aleat(0, 4320);
        chega = cria_evento(mundo, TIPO_CHEGA, BASEATUAL_H(mundo, h), -1, h, tempo, -1, -1); 
        fprio_insere (lef, chega, TIPO_CHEGA, tempo);
    }

    // para cada missao m:
    
    for(int m = 0; m < QTD_M_W(mundo); m++) {
        tempo = aleat(0, T_FIM_DO_MUNDO);
        missao = cria_evento(mundo, TIPO_MISSAO, -1, -1, -1, tempo, -1, m); 
        fprio_insere(lef, missao, TIPO_MISSAO, tempo);
    }

    // agendamento do evento fim:
    fim = cria_evento(mundo, TIPO_FIM, -1, -1, -1, T_FIM_DO_MUNDO, -1, -1);
    fprio_insere(lef, fim, TIPO_FIM, T_FIM_DO_MUNDO);
}

void evento_chega (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *espera;
    struct evento *desiste;
    int vai_esperar;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento chega");
        return;
    }

    BASEATUAL_H(mundo, ev -> heroi) = ev -> base;

    if (cjto_card(PRESENCA_B(mundo, ev -> base)) < LOTACAO_B(mundo, ev -> base) && !QTD_FILA_ESPERA_B(mundo, ev -> base))
        vai_esperar = 1;
    else {
        if (PACIENCIA_H(mundo, ev -> heroi) > (10 * QTD_FILA_ESPERA_B(mundo, ev -> base)))
            vai_esperar = 1;
        else
            vai_esperar = 0;
    }

    if (vai_esperar) {
        espera = cria_evento(mundo, TIPO_ESPERA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
        fprio_insere(lef, espera, TIPO_ESPERA, TEMPO_ATUAL_W(mundo));
        printa_evento(mundo, ev, vai_esperar);
    }   
    else {
        desiste = cria_evento(mundo, TIPO_DESISTE, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao); 
        fprio_insere(lef, desiste, TIPO_DESISTE, TEMPO_ATUAL_W(mundo));
        printa_evento(mundo, ev, vai_esperar);
    }
}

void evento_espera (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;
    int atual;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento espera");
        return;
    }

    atual = QTD_FILA_ESPERA_B(mundo, ev -> base);
    if (atual > MAX_FILA_B(mundo, ev -> base))
        MAX_FILA_B(mundo, ev -> base) = atual;

    fila_insere(FILA_ESPERA_B(mundo, ev -> base), ev -> heroi);

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao); 
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void evento_desiste (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *viaja;
    int baseproxnova;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento desiste");
        return;
    }

    baseproxnova = aleat(0, QTD_B_W(mundo) - 1);

    viaja = cria_evento(mundo, TIPO_VIAJA, ev -> base, baseproxnova, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, viaja, TIPO_VIAJA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void evento_avisa (W *mundo, struct fprio_t *lef, struct evento *ev) {
    int heroi;
    struct evento *entra;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento avisa");
        return;
    }

    while ((cjto_card(PRESENCA_B(mundo, ev -> base))) < LOTACAO_B(mundo, ev -> base) && fila_tamanho(FILA_ESPERA_B(mundo, ev -> base))) {
        fila_retira(FILA_ESPERA_B(mundo, ev -> base), &heroi);
        cjto_insere((PRESENCA_B(mundo, ev -> base)), heroi);
    }

    entra = cria_evento(mundo, TIPO_ENTRA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, entra, TIPO_ENTRA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void evento_entra (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *sai;
    int tpb;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento entra");
        return;
    }   

    tpb = 15 + PACIENCIA_H(mundo, ev -> heroi) * aleat(1, 20);

    sai = cria_evento(mundo, TIPO_SAI, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo) + tpb, ev -> distancia, ev -> missao);
    fprio_insere(lef, sai, TIPO_SAI, TEMPO_ATUAL_W(mundo));
  
    printa_evento(mundo, ev, tpb);
}

void evento_sai (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *viaja;
    struct evento *avisa;
    int baseproxnova;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento sai");
        return;
    }   

    baseproxnova = aleat(0, QTD_B_W(mundo) - 1);
    cjto_retira((PRESENCA_B(mundo, ev -> base)), ev -> heroi);

    viaja = cria_evento(mundo, TIPO_VIAJA, ev -> base, baseproxnova, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, viaja, TIPO_VIAJA, TEMPO_ATUAL_W(mundo));

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void evento_viaja (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *chega;
    double distancia;
    int duracao;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento viaja");
        return;
    }   

    distancia = distancia_bases(LOCAL_X_B(mundo, ev -> base), LOCAL_X_B(mundo, ev -> baseprox), LOCAL_Y_B(mundo, ev -> base), LOCAL_Y_B(mundo, ev -> baseprox));
    ev -> distancia = distancia;
    duracao = distancia / VELOCIDADE_H(mundo, ev -> heroi);

    chega = cria_evento(mundo, TIPO_CHEGA, ev -> baseprox, -1, ev -> heroi, TEMPO_ATUAL_W(mundo) + duracao, ev -> distancia, ev -> missao);
    fprio_insere(lef, chega, TIPO_CHEGA, TEMPO_ATUAL_W(mundo));

    printa_evento (mundo, ev, duracao);
}

void evento_morre (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento morre");
        return;
    }   

    cjto_retira((PRESENCA_B(mundo, ev -> base)), ev -> heroi);
    QTD_MORTE_W(mundo)++;
    STATUS_H(mundo, ev -> heroi) = 0;   
    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));

    printa_evento (mundo, ev, 0);
}

void evento_missao (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *morre;
    struct evento *missao;
    struct cjto_t *cjto_hab;
    struct cjto_t *cjto_hab_dabase;
    struct cjto_t *aux;

    int menor;
    int distancia;
    int idbase;
    int cumprida; //verifica se a missao foi cumprida ou nao

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento missao");
        return;
    }

    cjto_hab = cjto_cria(QTD_HAB_W(mundo));

    if (!cjto_hab) {
        printf("erro ao alocar cjto_hab");
        return;
    }

    menor = 99999999;

    for (int b = 0; b < QTD_B_W(mundo); b++) {
        distancia = distancia_bases(LOCAL_X_B(mundo, b), LOCAL_X_M(mundo, ev -> missao), LOCAL_Y_B(mundo, b), LOCAL_Y_B(mundo, ev -> missao));
        
        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", ev -> tempo, ev -> missao, b, distancia);
        cjto_imprime(PRESENCA_B(mundo, b));
        printf("]\n");
        
        for (int h = 0; h < QTD_H_W(mundo); h++) {
            if (cjto_pertence(PRESENCA_B(mundo, b), h)) {
                printf("%6d: MISSAO %d HAB HEROI %d: [ ", ev -> tempo, ev -> missao, h);
                cjto_imprime(HABILIDADES_H(mundo, h));
                printf(" ]\n");
            }
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", ev -> tempo, ev -> missao, b);
        
        for(int h = 0; h < QTD_H_W(mundo); h++) {
            if (cjto_pertence(PRESENCA_B(mundo, b), h)) {
                aux = cjto_uniao(cjto_hab, HABILIDADES_H(mundo, h));
                cjto_destroi(cjto_hab);
                cjto_hab = aux;
            }
        }

        cjto_imprime(cjto_hab);
        printf(" ]\n");

        if (distancia < menor) {
            menor = distancia;
            idbase = b; 
        }
    }

    cjto_hab_dabase = cjto_cria(QTD_HAB_W(mundo));

    if (!cjto_hab_dabase) {
        printf("erro ao alocar cjto_hab_dabase");
        return;
    }

    for (int h = 0; h < QTD_H_W(mundo); h++) {
        if (cjto_pertence(PRESENCA_B(mundo, idbase), h)) {
            aux = cjto_uniao(cjto_hab_dabase, HABILIDADES_H(mundo, h));
            cjto_destroi(cjto_hab_dabase);
            cjto_hab_dabase = aux;
        }
    }
    
    if (distancia == menor && cjto_iguais(cjto_hab, HABILIDADES_M(mundo, ev -> missao))) {
        incrementa_xp(mundo, idbase);
        cumprida = 1;
        QTD_MI_W(mundo)++;
        QTD_M_B(mundo, idbase)++;
    }
    else {
        if (COMPOSTOS_W(mundo) && !(TEMPO_ATUAL_W(mundo) % 2500)) {
            COMPOSTOS_W(mundo)--;
            cumprida = 1;
            QTD_MI_W(mundo)++;
            QTD_M_B(mundo, idbase)++;        
            morre = cria_evento(mundo, TIPO_MORRE, idbase, ev -> baseprox, acha_experiente(mundo), TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
            fprio_insere(lef, morre, TIPO_MORRE, TEMPO_ATUAL_W(mundo));
            incrementa_xp(mundo, idbase);
        }
        else {
            missao = cria_evento(mundo, TIPO_MISSAO, idbase, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo) + 24*60, ev-> distancia, ev -> missao);
            fprio_insere(lef, missao, TIPO_MISSAO, TEMPO_ATUAL_W(mundo) + 24*60);
            cumprida = 0;
        }
    }

    TENTATIVA_M(mundo, ev -> missao)++;

    if (TENTATIVA_M(mundo, ev -> missao) < MIN_TENT_M(mundo))
        MIN_TENT_M(mundo) = TENTATIVA_M(mundo, ev -> missao);

    if (TENTATIVA_M(mundo, ev -> missao) > MAX_TENT_M(mundo))
        MAX_TENT_M(mundo) = TENTATIVA_M(mundo, ev -> missao);          
    SOMA_TENT_M(mundo)++;

    printa_missao(mundo, ev, cjto_hab_dabase, TENTATIVA_M(mundo, ev -> missao), cumprida);

    cjto_destroi(cjto_hab);
    cjto_destroi(cjto_hab_dabase);
}

void evento_fim (W *mundo, struct fprio_t *lef, struct evento *ev) {

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento fim");
        return;
    }

    fprio_destroi(lef);
    printa_evento(mundo, ev, 0);
}


















