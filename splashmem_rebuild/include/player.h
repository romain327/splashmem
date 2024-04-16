#ifndef SPLASHMEM2_PLAYER_H
#define SPLASHMEM2_PLAYER_H

#include "params.h"
#include "inits.h"
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

typedef struct s_player
{
    SDL_Rect p;
    uint32_t id;
    uint32_t x;
    uint32_t y;
    uint32_t *color;
    int32_t credits;
    uint32_t last_bomb;
    uint8_t bomb_drop;
    uint8_t is_done;
    char (*get_action)();
} Player;

Player* init_player(uint32_t nb_player, uint8_t num, char *lib);
void link_player(Player *player, char *lib);
uint32_t **init_player_pos(uint32_t argc, uint8_t num);

#endif //SPLASHMEM2_PLAYER_H
