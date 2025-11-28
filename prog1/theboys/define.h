#ifndef DEFINE_H
#define DEFINE_H

// definições do trabalho:
#define T_INICIO                 0
#define T_FIM_DO_MUNDO           525600
#define N_TAMANHO_MUNDO          20000
#define N_HABILIDADES            10
#define N_HEROIS                 (N_HABILIDADES * 5)
#define N_BASES                  (N_HEROIS / 5)
#define N_MISSOES                (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V            (N_HABILIDADES * 3)
 
// tipos dos eventos:
#define TIPO_CHEGA               1
#define TIPO_ESPERA              2
#define TIPO_DESISTE             3
#define TIPO_AVISA               4
#define TIPO_ENTRA               5
#define TIPO_SAI                 6
#define TIPO_VIAJA               7
#define TIPO_MORRE               8
#define TIPO_MISSAO              9
#define TIPO_FIM                 10

// macros para o codigo ficar mais legivel:
/*
 * H: heroi
 * B: base
 * W: world (mundo)
 * M: missao
 *
*/

// acesso a vetores do mundo, para implementacao dos outros defines
#define COMPOSTOS(w)             ((w) -> compstv)
#define TEMPO_ATUAL_W(w)         ((w) -> clk)
#define QTD_E(w)                 ((w) -> qtd_ev)
#define QTD_MI(w)                ((w) -> qtd_mi) 
#define BASE(w, b)               ((w) -> vet_B[(b)])
#define HEROI(w, h)              ((w) -> vet_H[(h)])
#define MISSAO(w, m)             ((w) -> vet_M[(m)])

// campos das bases
#define LOTACAO_B(w, b)          (BASE((w), (b)).lotacao)
#define PRESENCA_B(w, b)         (BASE((w), (b)).presenca)
#define OCUPACAO_B(w, b)         (BASE((w), (b)).presenca -> num)
#define FILA_ESPERA_B(w, b)      (BASE((w), (b)).espera)
#define QTD_FILA_ESPERA_B(w, b)  (BASE((w), (b)).espera -> num)
#define LOCAL_X_B(w, b)          (BASE((w), (b)).local.x)
#define LOCAL_Y_B(w, b)          (BASE((w), (b)).local.y)
#define ID_B(w, b)               (BASE((w), (b)).id)

// campos dos herois
#define PACIENCIA_H(w, h)        (HEROI((w), (h)).paciencia)
#define BASEATUAL_H(w, h)        (HEROI((w), (h)).baseatual)
#define VELOCIDADE_H(w, h)       (HEROI((w), (h)).velocidade)
#define STATUS_H(w, h)           (HEROI((w), (h)).status)
#define HABILIDADES_H(w, h)      (HEROI((w), (h)).habilidades) 
#define ID_H(w, h)               (HEROI((w), (h)).id)
#define XP_H(w, h)               (HEROI((w), (h)).xp)

// campos das missoes
#define LOCAL_X_M(w, m)          (MISSAO((w), (m)).local.x) 
#define LOCAL_Y_M(w, m)          (MISSAO((w), (m)).local.y) 
#define HABILIDADES_M(w, m)      (MISSAO((w), (m)).habilidades)
#define ID_M(w, m)               (MISSAO((w), (m)).id)
#define TENTATIVA_M(w, m)        (MISSAO((w), (m)).tentativa)

#endif