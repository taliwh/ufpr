#ifndef __STATE__
#define __STATE__

// renderiza o comeco do jogo com os botoes de jogar e sair
void render_menu(struct game *catland);

// recebe entrada do mouse ao clicar nos botoes do menu
void input_menu(struct game *catland);

// atualiza a fisica, a logica e desenha o frame do jogo no estado play
// ao final verifica se o player morreu ou venceu e muda o estado
void render_play(struct game *catland);

// renderiza o final do jogo com os botoes de recomecar e sair, com musica triste
void render_gameover(struct game *catland);

// recebe entrada do mouse ao clicar nos botoes do estado gameover ou do estado win
void input_gameover_win(struct game *catland);

// renderiza o pause, com botoes de continuar e sair
void render_pause(struct game *catland);

// recebe entrada do mouse ao clicar nos botoes do estado pause
void input_pause(struct game *catland);

// renderiza a comemoracao do jogo caso o player tenha conseguido ir ate o final
void render_win(struct game *catland);

#endif