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
 * _H: heroi
 * _B: base
 * _W: world (mundo)
 * _M: missao
 *
*/

// acesso a vetores do mundo, para implementacao dos outros defines
#define COMPOSTOS_W(w)           ((w) -> qtd_compstv)
#define QTD_HAB_W(w)             ((w) -> qtd_hab)
#define QTD_H_W(w)               ((w) -> qtd_H)
#define QTD_B_W(w)               ((w) -> qtd_B)
#define QTD_M_W(w)               ((w) -> qtd_M)
#define QTD_E_W(w)               ((w) -> qtd_ev)
#define QTD_MI_W(w)              ((w) -> qtd_mi) 
#define QTD_MORTE_W(w)           ((w) -> qtd_morte)
#define MIN_TENT_W(w)            ((w) -> min_tent)
#define MAX_TENT_W(w)            ((w) -> max_tent) 
#define SOMA_TENT_W(w)           ((w) -> soma_tent)
#define HEROI_W(w, h)            ((w) -> vet_H[(h)])
#define BASE_W(w, b)             ((w) -> vet_B[(b)])
#define MISSAO_W(w, m)           ((w) -> vet_M[(m)])
#define TEMPO_ATUAL_W(w)         ((w) -> clk)
#define LOCAL_X_W(w)             ((w) -> local.x)
#define LOCAL_Y_W(w)             ((w) -> local.y)
#define DISTANCIAS_W(w, d)       ((w) -> vet_dist[(d)])
#define DIST_ID_B(w, d)          (DISTANCIAS_W((w), (d)).id_base)
#define DIST_DIST(w, d)          (DISTANCIAS_W((w), (d)).dist)    
                                    
// campos das bases
#define LOTACAO_B(w, b)          (BASE_W((w), (b)).lotacao)
#define PRESENCA_B(w, b)         (BASE_W((w), (b)).presenca)
#define FILA_ESPERA_B(w, b)      (BASE_W((w), (b)).espera)
#define MAX_FILA_B(w, b)         (BASE_W((w), (b)).max_fila)
#define LOCAL_X_B(w, b)          (BASE_W((w), (b)).local.x)
#define LOCAL_Y_B(w, b)          (BASE_W((w), (b)).local.y)
#define ID_B(w, b)               (BASE_W((w), (b)).id)
#define QTD_M_B(w, b)            (BASE_W((w), (b)).qtd_m)

// campos dos herois
#define PACIENCIA_H(w, h)        (HEROI_W((w), (h)).paciencia)
#define BASEATUAL_H(w, h)        (HEROI_W((w), (h)).baseatual)
#define VELOCIDADE_H(w, h)       (HEROI_W((w), (h)).velocidade)
#define STATUS_H(w, h)           (HEROI_W((w), (h)).status)
#define HABILIDADES_H(w, h)      (HEROI_W((w), (h)).habilidades) 
#define ID_H(w, h)               (HEROI_W((w), (h)).id)
#define XP_H(w, h)               (HEROI_W((w), (h)).xp)

// campos das missoes
#define LOCAL_X_M(w, m)          (MISSAO_W((w), (m)).local.x) 
#define LOCAL_Y_M(w, m)          (MISSAO_W((w), (m)).local.y) 
#define HABILIDADES_M(w, m)      (MISSAO_W((w), (m)).habilidades)
#define ID_M(w, m)               (MISSAO_W((w), (m)).id)
#define TENTATIVA_M(w, m)        (MISSAO_W((w), (m)).tentativa)


#endif