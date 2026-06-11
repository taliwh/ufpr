#ifndef __SAVE__
#define __SAVE__

#include "game.h"

int save_exists();
void save_game(struct game *catland);
void load_game(struct game *catland);

#endif