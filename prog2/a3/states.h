#ifndef __STATE__
#define __STATE__

void render_menu(struct game *catland);
void input_menu(struct game *catland);
void render_play(struct game *catland);
void render_gameover(struct game *catland);
void input_gameover_win(struct game *catland);
void input_pause(struct game *catland);
void render_pause(struct game *catland);
void render_win(struct game *catland);

#endif