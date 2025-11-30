#include "eventos.h"

// struct dos eventos, opaca para o usuario.
struct evento {
    int tipo;
    int base;
    int baseprox; 
    int heroi;
    int tempo;
    int missao;
};

// retorna um numero aleatorio entre um intervalo utilizando rand ().
int aleat (int min, int max) {
    int aleat;

    aleat = min + rand () % (max - min + 1);

    return aleat;
}

// calcula a distancia baseada na seguinte formula euclidiana:
// distancia = raiz de [(x2 - x1)² + (y2 - y1)²].
int distancia_bases(int x1, int x2, int y1, int y2) {
    int dx, dy;

    dx = x2 - x1;
    dy = y2 - y1;

    return hypot(dx, dy);
}

// retorna o vetor modificado de tal forma que v[a, b] eh um vetor ordenado.
// essa funcao é utilizada como auxiliar para a funcao merge_sort.
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

// o merge sort divide o vetor em várias partes recursivamente, 
// e ordena cada parte utilizando a funcao intercala.
// faz isso até retornar o vetor completo ordenado.
struct distancia *merge_sort(struct distancia *vetor, int ini, int fim) {
    int meio;

    if (ini >= fim)
        return vetor;

    meio = (ini + fim) / 2;
    merge_sort(vetor, ini, meio);
    merge_sort(vetor, meio + 1, fim);

    return intercala(vetor, ini, meio, fim);
}   

// incrementa o xp dos herois da base:
// percorre os herois e verifica se aquele heroi pertence na base dada por parametro e se está vivo.
// caso seja verdade, incrementa seu xp em 1.
void incrementa_xp(W *mundo, int idbase) {
    if (!mundo)
        return;

    for(int h = 0; h < QTD_H_W(mundo); h++) 
        if (cjto_pertence(PRESENCA_B(mundo, idbase), h) == 1 && HEROI_W(mundo, h).status)
            HEROI_W(mundo, h).xp++;
}

// retorna o id do heroi mais top ( o mais experiente, com mais xp acumulado ).
// se o heroi pertence a base dada por parametro, compara ele com o maior xp ja encontrado.
// em seguida, guarda o id do heroi com mais experiencia utilizando a variavel idheroi.
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

// retorna a uniao das habilidades dos herois pertencentes a base dada como parametro.
// percorre os herois e verifica se eles pertencem aquela base, se sim, eh utilizada uma
// variavel aux para evitar vazamento de memoria, para nao sobrescrever a variavel cjto_hab.
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

// retorna o status da vida de um heroi, verifica isso utilizando a macro status_h.
// utiliza tambem (ev -> heroi < 0), para verificar se o evento eh uma missao e nao 
// tem o heroi inicializado (-1).
int status_vida (W *mundo, struct evento *ev) {
    if (STATUS_H(mundo, ev -> heroi) || ev -> heroi < 0)
        return 1;
    return 0;
}

// aloca um evento e o retorna.
// atribui valores com base no que a funcao recebe por parametro.
// se falhar a alocacao, retorna null.
struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, int missao) {
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

    return evento_novo;
}

// printa todos os eventos, com excessao do evento missao, que eh o mais complicado.
// antes, eh necessario a verificacao dos ponteiros para retornar falha.
// a quantidade total de eventos completos eh aumentada.
// o aux é utilizado para eventos especificos, nos casos em que temos que printar 
// o tempo + um adicional, ou alguma formula especifica, ou a distancia.
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
                printf("%6d: CHEGA  HEROI %2d BASE %d (%2d /%2d ) ESPERA\n", ev -> tempo, ev -> heroi, ev -> base, cjto_card(PRESENCA_B(mundo, ev -> base)), LOTACAO_B(mundo, ev -> base));
            else
                printf("%6d: CHEGA  HEROI %2d BASE %d (%2d /%2d ) DESISTE\n", ev -> tempo, ev -> heroi, ev -> base, cjto_card(PRESENCA_B(mundo, ev -> base)), LOTACAO_B(mundo, ev -> base));
            break;

        case TIPO_ESPERA:
            printf("%6d: ESPERA HEROI %2d BASE %d (%2d )\n", ev -> tempo, ev -> heroi, ev -> base, fila_tamanho(FILA_ESPERA_B(mundo, ev -> base)));
            break;

        case TIPO_DESISTE:
            printf("%6d: DESIST HEROI %2d BASE %d\n", ev -> tempo, ev -> heroi, ev -> base);
            break;

        case TIPO_AVISA:
            printf("%6d: AVISA  PORTEIRO BASE %d (%2d /%2d ) FILA [ ", ev -> tempo, ev -> base, cjto_card(PRESENCA_B(mundo, ev -> base)), LOTACAO_B(mundo, ev -> base));
            fila_imprime(FILA_ESPERA_B(mundo, ev -> base));
            printf(" ]\n");
            printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", ev -> tempo, ev -> base, ev -> heroi);
            break;

        case TIPO_ENTRA:
            printf("%6d: ENTRA  HEROI %2d BASE %d (%2d /%2d ) SAI %d\n", ev -> tempo, ev -> heroi, ev -> base, cjto_card(PRESENCA_B(mundo, ev -> base)), LOTACAO_B(mundo, ev -> base), ev -> tempo + aux);
            break;

        case TIPO_SAI:
            printf("%6d: SAI    HEROI %2d BASE %d (%2d /%2d )\n", ev -> tempo, ev -> heroi, ev -> base, cjto_card(PRESENCA_B(mundo, ev -> base)), LOTACAO_B(mundo, ev -> base));
            break;

        case TIPO_VIAJA:
            printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", ev -> tempo, ev -> heroi, ev -> base, ev -> baseprox, aux, VELOCIDADE_H(mundo, ev -> heroi), ev -> tempo + (aux / VELOCIDADE_H(mundo, ev -> heroi)));
            break;

        case TIPO_MORRE:
            printf("%6d: MORRE HEROI %2d MISSAO %d\n",  ev -> tempo, ev -> heroi, ev -> missao);
            break;

        case TIPO_FIM:
            printf("FIM\n\n");

            for(int h = 0; h < QTD_H_W(mundo); h++)
                if (STATUS_H(mundo, h)) {
                    printf("HEROI %2d VIVO   PAC %3d VEL %4d EXP %4d HABS [ ", h, PACIENCIA_H(mundo, h), VELOCIDADE_H(mundo, h), XP_H(mundo, h));
                    cjto_imprime(HABILIDADES_H(mundo, h));
                    printf(" ]\n");
                }
                else {
                    printf("HEROI %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ", h, PACIENCIA_H(mundo, h), VELOCIDADE_H(mundo, h), XP_H(mundo, h));
                    cjto_imprime(HABILIDADES_H(mundo, h));
                    printf(" ]\n");                   
                }
            

            for(int b = 0; b < QTD_B_W(mundo); b++) 
                printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", b, LOTACAO_B(mundo, b), MAX_FILA_B(mundo, b), QTD_M_B(mundo, b));

            printf("EVENTOS TRATADOS: %d\n", QTD_E_W(mundo));
            printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", QTD_MI_W(mundo), QTD_M_W(mundo), (QTD_MI_W(mundo) * 100.0) / QTD_M_W(mundo));
            printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", MIN_TENT_W(mundo), MAX_TENT_W(mundo), (SOMA_TENT_W(mundo) * 1.0) / QTD_MI_W(mundo));
            printf("TAXA DE MORTALIDADE: %.1f%%\n", (QTD_MORTE_W(mundo) * 100.0) / QTD_H_W(mundo));
            break;
    }
}

// printa somente o evento missao, sem incluir as depuracoes, pois estas sao incluidas no propio evento.
// aumenta a quantidade de eventos completos do mundo e analisa se a missao foi cumprida,
// para imprimir conforme o seu estado.
void printa_missao (W *mundo, struct evento *ev, struct cjto_t *hab, int cumprida){
    if (!mundo || !ev)
        return;

    QTD_E_W(mundo)++;
    
    if (cumprida) {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", ev -> tempo, ev -> missao, ev -> base);
        cjto_imprime(hab);
        printf(" ]\n");
    }
    else
        printf("%6d: MISSAO %d IMPOSSIVEL\n", ev -> tempo, ev -> missao);
}

// inclui na lef os eventos iniciais, inicializando os campos com os dados que foram passados pelo trabalho.
// eventos nos quais nao precisam de certo parametro para serem criados, sao inicializados com -1.
// o evento fim eh agendado com o tempo do fim do mundo.
void eventos_iniciais (W *mundo, struct fprio_t *lef) {
    struct evento *chega, *missao, *fim;
    int tempo;

    if (!lef || !mundo) {
        printf("falha em realizar eventos iniciais");
        return;
    }

    // para cada heroi:
    for (int h = 0; h < QTD_H_W(mundo); h++) {
        BASEATUAL_H(mundo, h) = aleat(0, QTD_B_W(mundo) -1);
        tempo = aleat(0, 4320);
        chega = cria_evento(mundo, TIPO_CHEGA, BASEATUAL_H(mundo, h), -1, h, tempo, -1); 
        fprio_insere (lef, chega, TIPO_CHEGA, tempo);
    }

    // para cada missao m:
    for(int m = 0; m < QTD_M_W(mundo); m++) {
        tempo = aleat(0, T_FIM_DO_MUNDO);
        missao = cria_evento(mundo, TIPO_MISSAO, -1, -1, -1, tempo, m); 
        fprio_insere(lef, missao, TIPO_MISSAO, tempo);
    }

    // agendamento do evento fim:
    fim = cria_evento(mundo, TIPO_FIM, -1, -1, -1, T_FIM_DO_MUNDO, -1);
    fprio_insere(lef, fim, TIPO_FIM, T_FIM_DO_MUNDO);
}

// funcao responsavel pelo evento chega : 
// atualiza a base do heroi inserindo a base do evento na struct do heroi.
// se o heroi for esperar, insere o evento espera na lef e imprime.
// caso contrario, insere o evento desiste na lef e imprime.
void evento_chega (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *espera, *desiste;
    int vai_esperar;

    if (!mundo || !lef || !ev) 
        return;

    BASEATUAL_H(mundo, ev -> heroi) = ev -> base;

    if (cjto_card(PRESENCA_B(mundo, ev -> base)) < LOTACAO_B(mundo, ev -> base) && !fila_tamanho(FILA_ESPERA_B(mundo, ev -> base)))
        vai_esperar = 1;
    else 
        if (PACIENCIA_H(mundo, ev -> heroi) > (10 * fila_tamanho(FILA_ESPERA_B(mundo, ev -> base))))
            vai_esperar = 1;
        else
            vai_esperar = 0;
    
    if (vai_esperar) {
        espera = cria_evento(mundo, TIPO_ESPERA, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo, ev -> missao);
        fprio_insere(lef, espera, TIPO_ESPERA, ev -> tempo); 
        printa_evento(mundo, ev, vai_esperar);
    }   
    else {
        desiste = cria_evento(mundo, TIPO_DESISTE, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo, ev -> missao); 
        fprio_insere(lef, desiste, TIPO_DESISTE, ev -> tempo);
        printa_evento(mundo, ev, vai_esperar);
    }
}

// funcao responsavel pelo evento espera:
// insere o heroi na fila de espera usando a funcao fila_insere.
// printa o evento antes de inserir o evento avisa, pois se inserissemos 
// antes de printar, o tamanho da fila apareceria errado (com 1 pessoa a mais).
// cria e insere o evento avisa na lef.
void evento_espera (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;
    int atual;

    if (!mundo || !lef || !ev) 
        return;

    fila_insere(FILA_ESPERA_B(mundo, ev -> base), ev -> heroi);
    printa_evento(mundo, ev, 0);

    atual = fila_tamanho(FILA_ESPERA_B(mundo, ev -> base));
    if (atual > MAX_FILA_B(mundo, ev -> base))
        MAX_FILA_B(mundo, ev -> base) = atual;

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo, ev -> missao); 
    fprio_insere(lef, avisa, TIPO_AVISA, ev -> tempo);

}

// funcao responsavel pelo evento desiste:
// aleatoriza uma base destino, para o heroi poder viajar para la com o evento viaja
// cria e insere o evento viaja com a nova base aleatorizada na lef
void evento_desiste (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *viaja;
    int baseproxnova;

    if (!mundo || !lef || !ev) 
        return;

    baseproxnova = aleat(0, QTD_B_W(mundo) - 1);

    viaja = cria_evento(mundo, TIPO_VIAJA, ev -> base, baseproxnova, ev -> heroi, ev -> tempo, ev -> missao);
    fprio_insere(lef, viaja, TIPO_VIAJA, ev -> tempo);

    printa_evento(mundo, ev, 0);
}

// funcao responsavel pelo evento avisa:
// enquanto a base nao esta vazia, o heroi e retirado da fila de espera e inserido na base.
// isso eh realizado com o cjto_insere e com a insercao do evento entra na lef.
void evento_avisa (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *entra;
    int heroi;

    if (!mundo || !lef || !ev) 
        return;

    while ((cjto_card(PRESENCA_B(mundo, ev -> base))) < LOTACAO_B(mundo, ev -> base) && fila_tamanho(FILA_ESPERA_B(mundo, ev -> base))) {
        printa_evento(mundo, ev, 0);      
        fila_retira(FILA_ESPERA_B(mundo, ev -> base), &heroi);
        entra = cria_evento(mundo, TIPO_ENTRA, ev -> base, ev -> baseprox, heroi, ev -> tempo, ev -> missao);
        fprio_insere(lef, entra, TIPO_ENTRA, ev -> tempo);
        cjto_insere((PRESENCA_B(mundo, ev -> base)), heroi);
    }
}

// funcao responsavel pelo evento entra:
// calcula o tempo de permanencia (tpb) do heroi na base.
// cria e insere na lef o evento sai para o heroi sair após o tempo de permanencia.
void evento_entra (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *sai;
    int tpb;

    if (!mundo || !lef || !ev) 
        return;

    tpb = 15 + PACIENCIA_H(mundo, ev -> heroi) * aleat(1, 20);

    sai = cria_evento(mundo, TIPO_SAI, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo + tpb, ev -> missao);
    fprio_insere(lef, sai, TIPO_SAI, ev -> tempo + tpb);
  
    printa_evento(mundo, ev, tpb);
}

// funcao responsavel pelo evento sai:
// o heroi vai se dirigir para uma outra base, por isso aleatorizamos sua proxima base.
// inserimos na lef o evento viaja para a proxima base, e o evento avisa para avisar o porteiro.
void evento_sai (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *viaja, *avisa;
    int baseproxnova;
    
    if (!mundo || !lef || !ev) 
        return;

    baseproxnova = aleat(0, QTD_B_W(mundo) - 1);
    cjto_retira((PRESENCA_B(mundo, ev -> base)), ev -> heroi);

    viaja = cria_evento(mundo, TIPO_VIAJA, ev -> base, baseproxnova, ev -> heroi, ev -> tempo, ev -> missao);
    fprio_insere(lef, viaja, TIPO_VIAJA, ev -> tempo);

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo, ev -> missao);
    fprio_insere(lef, avisa, TIPO_AVISA, ev -> tempo);

    printa_evento(mundo, ev, 0);
}

// funcao responsavel pelo evento viaja:
// calcula-se a distancia da base atual do heroi para a base proxima,
// utilizando a funcao distancia_bases. a duracao eh calculada com a formula dada pelo enunciado.
// cria e insere na lef o evento chega com a base destino.
void evento_viaja (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *chega;
    int distancia, duracao;

    if (!mundo || !lef || !ev) 
        return;

    distancia = distancia_bases(LOCAL_X_B(mundo, ev -> base), LOCAL_X_B(mundo, ev -> baseprox), LOCAL_Y_B(mundo, ev -> base), LOCAL_Y_B(mundo, ev -> baseprox));
    duracao = distancia / VELOCIDADE_H(mundo, ev -> heroi);

    chega = cria_evento(mundo, TIPO_CHEGA, ev -> baseprox, -1, ev -> heroi, ev -> tempo + duracao, ev -> missao);
    fprio_insere(lef, chega, TIPO_CHEGA, ev -> tempo + duracao);

    printa_evento (mundo, ev, distancia);
}

// funcao responsavel pelo evento morre:
// o heroi é retirado da base e sua morte eh contabilizada, com seu status atualizado.
// o evento avisa e criado e inserido na lef para avisar o porteiro da morte.
void evento_morre (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;

    if (!mundo || !lef || !ev) 
        return;

    cjto_retira((PRESENCA_B(mundo, ev -> base)), ev -> heroi);

    QTD_MORTE_W(mundo)++;
    STATUS_H(mundo, ev -> heroi) = 0;   

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo, ev -> missao);
    fprio_insere(lef, avisa, TIPO_AVISA, ev -> tempo);

    printa_evento (mundo, ev, 0);
}

// funcao responsavel pelo evento missao:
// primeiro eh impresso a tentativa n da missao.
// depois, eh inserido no vetor de distancias (vet_dist) todas as distancias das bases ate a missao.
// apos isso, ordenamos as distancias com a funcao do algoritmo recursivo merge_sort.
// enquanto ainda nao achamos a base perfeita (com a menor distancia e com as habilidades requeridas):
// imprimos as depuracoes;
// eh criado uma variavel chamada habs_base, com as habilidades da base de menor distancia obtidas pela funcao habilidades_base;
// imprimimos mais uma depuracao, imprimindo habs_base
// se a base d emenor distancia nao tiver as habilidades requeridas, percorremos mais uma vez o laco fazendo b_+ pra pegar a segunda base mais perto e assim pordiantekkafmeu
void evento_missao (W *mundo, struct fprio_t *lef, struct evento *ev) {
    int idbase_proxima, b, heroitop, cumprida, existe_bmp;
    struct cjto_t *habs_base;
    struct evento *morre;
    struct evento *missao;

    if (!mundo || !lef || !ev) 
        return;

    b = 0;
    idbase_proxima = -1;
    cumprida = 0;
    existe_bmp = 0;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", ev -> tempo, ev -> missao, TENTATIVA_M(mundo, ev -> missao));
    cjto_imprime(HABILIDADES_M(mundo, ev -> missao));
    printf(" ]\n");

    for (b = 0; b < QTD_B_W(mundo); b++) {
        DIST_ID_B(mundo, b) = b;
        DIST_DIST(mundo, b) = distancia_bases(LOCAL_X_B(mundo, b), LOCAL_X_M(mundo, ev -> missao), LOCAL_Y_B(mundo, b), LOCAL_Y_M(mundo, ev -> missao));
    }   

    merge_sort(&DISTANCIAS_W(mundo, 0), 0, QTD_B_W(mundo) - 1);

    b = 0;

    while (!existe_bmp && b < QTD_B_W(mundo)) {
        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", ev->tempo, ev->missao, DIST_ID_B(mundo, b), DIST_DIST(mundo, b));
        cjto_imprime(PRESENCA_B(mundo, DIST_ID_B(mundo, b)));
        printf(" ]\n");

        for (int h = 0; h < QTD_H_W(mundo); h++) {
            if (cjto_pertence(PRESENCA_B(mundo, DIST_ID_B(mundo, b)), h)) {
                printf("%6d: MISSAO %d HAB HEROI %2d: [ ", ev->tempo, ev->missao, h);
                cjto_imprime(HABILIDADES_H(mundo, h));
                printf(" ]\n");
            }
        }

        habs_base = habilidades_base(mundo, DIST_ID_B(mundo, b));

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", ev->tempo, ev->missao, DIST_ID_B(mundo, b));
        cjto_imprime(habs_base);
        printf(" ]\n");

        if (cjto_contem(habs_base, HABILIDADES_M(mundo, ev -> missao))) {
            existe_bmp = 1;
            idbase_proxima = DIST_ID_B(mundo, b);
        }

        cjto_destroi(habs_base);

        b++;
    }

    if (existe_bmp) {
        cumprida++;
        incrementa_xp(mundo, idbase_proxima);
        QTD_MI_W(mundo)++;
        QTD_M_B(mundo, idbase_proxima)++;

        habs_base = habilidades_base(mundo, idbase_proxima);
        ev -> base = idbase_proxima;

        printa_missao(mundo, ev, habs_base, cumprida);
        cjto_destroi(habs_base);
    }
    else 
        if (COMPOSTOS_W(mundo) && !(ev -> tempo % 2500)) {
            COMPOSTOS_W(mundo)--;
            cumprida++;
            ev -> base = DIST_ID_B(mundo, 0);

            heroitop = acha_experiente(mundo, DIST_ID_B(mundo, 0));
            if (heroitop != -1) {
                morre = cria_evento(mundo, TIPO_MORRE, DIST_ID_B(mundo, 0), ev -> baseprox, heroitop, ev -> tempo, ev -> missao);
                fprio_insere(lef, morre, TIPO_MORRE, ev -> tempo);
            }

            incrementa_xp(mundo, DIST_ID_B(mundo, 0));
            QTD_MI_W(mundo)++;
            QTD_M_B(mundo, DIST_ID_B(mundo, 0))++;

            habs_base = habilidades_base(mundo, DIST_ID_B(mundo, 0));

            printa_missao(mundo, ev, habs_base, cumprida);
            cjto_destroi(habs_base);
        }
        else {
            missao = cria_evento(mundo, TIPO_MISSAO, ev -> base, ev -> baseprox, ev -> heroi, ev -> tempo + 24*60, ev -> missao);
            fprio_insere(lef, missao, TIPO_MISSAO, ev -> tempo + 24*60);

            printa_missao(mundo, ev, NULL, cumprida);
            TENTATIVA_M(mundo, ev -> missao)++; 
        }

    if (TENTATIVA_M(mundo, ev -> missao) < MIN_TENT_W(mundo) || MIN_TENT_W(mundo) == -1)
        MIN_TENT_W(mundo) = TENTATIVA_M(mundo, ev -> missao);

    if (TENTATIVA_M(mundo, ev -> missao) > MAX_TENT_W(mundo) || MAX_TENT_W(mundo) == -1)
        MAX_TENT_W(mundo) = TENTATIVA_M(mundo, ev -> missao);
    
    SOMA_TENT_W(mundo) = SOMA_TENT_W(mundo) + TENTATIVA_M(mundo, ev->missao);
}

void evento_fim (W *mundo, struct fprio_t *lef, struct evento *ev) {

    if (!mundo || !lef || !ev) 
        return;
    
    fprio_destroi(lef);
    printa_evento(mundo, ev, 0);
}


















