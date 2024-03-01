#include <stdlib.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "param.h"

int start_pos_x[] = {MAP_SIZE/4, MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE*3/4};
int start_pos_y[] = {MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE/4, MAP_SIZE*3/4};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void player_init(t_player* p_player, uint8_t num)
{
    p_player->id = num + 1;
    p_player->color = 0;
    p_player->x = start_pos_x[num];
    p_player->y = start_pos_y[num];
    p_player->data = NULL;
    p_player->credits = P_CREDITS;
    p_player->count = 0;
    p_player->last_bomb = 0;
	p_player->bomb_drop = 0;
    p_player->is_done = 0;
}