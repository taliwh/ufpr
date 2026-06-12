#ifndef __SAVE__
#define __SAVE__

#include "game.h"

// retorna 1 se existe um arquivo de save salvo
int save_exists();

// grava o estado atual do jogo no disco
void save_game(struct game *catland);

// restaura o jogo a partir do arquivo de save
void load_game(struct game *catland);

#endif