#ifndef SPLASHMEM_ENTITIES_H
#define SPLASHMEM_ENTITIES_H

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "params.h"

/***********************************************************************************/
/*                                       BOMB                                      */
/***********************************************************************************/
typedef struct s_bomb {
    uint32_t x;
    uint32_t y;
    int32_t timer;
} Bomb;

void init_bomb(Bomb *bomb);

/***********************************************************************************/
/*                                      PLAYER                                     */
/***********************************************************************************/
typedef struct s_player {
    char *name;
    char *lib_name;
    SDL_Rect p;
    uint32_t id;
    uint32_t x;
    uint32_t y;
    SDL_Color player_color;
    int32_t credits;
    uint32_t score;
    Bomb *bombs[BOMB_TIMER];
    uint8_t is_done;
    char (*get_action)();
} Player;

Player* init_player(uint32_t nb_player, uint8_t num, char *lib);
void link_player(Player *player, char *lib);
void get_name_and_lib(char *filename, Player *player);
uint32_t **init_player_pos(uint32_t argc, uint8_t num);
SDL_Color init_player_color(uint8_t num);

/***********************************************************************************/
/*                                       MAP                                       */
/***********************************************************************************/
typedef struct s_cell {
    uint32_t x;
    uint32_t y;
    SDL_Color color;
    SDL_Rect rect;
} Cell;

void bomb_explode(Bomb *bomb, Cell map[MAP_SIZE][MAP_SIZE], Player **players);

uint32_t init_map(Cell map[MAP_SIZE][MAP_SIZE]);
uint32_t init_player_pos_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player **players, uint32_t nb_player);
uint32_t compare_color(SDL_Color c1, SDL_Color c2);
void update_score(Player **players, Cell map[MAP_SIZE][MAP_SIZE], uint32_t nb_player);

#endif //SPLASHMEM_ENTITIES_H
