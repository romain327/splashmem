#ifndef SPLASHMEM_ENTITIES_H
#define SPLASHMEM_ENTITIES_H

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_Mixer.h>
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
void bombs_toString(Bomb *bombs[BOMB_TIMER]);

/***********************************************************************************/
/*                                      IMAGES                                     */
/***********************************************************************************/

typedef struct s_bmp_player
{
    SDL_Texture* bmp_haut[2];
    SDL_Texture* bmp_droit[2];
    SDL_Texture* bmp_gauche[2];
    SDL_Texture* bmp_bas[2];
    SDL_Texture* bmp_mort;
    SDL_Texture* bmp_ultime[8];
    SDL_Texture* bmp_catch[2];
} t_bmp_player;

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

    t_bmp_player bmp;
    uint32_t x_avant;
    uint32_t y_avant;
    uint32_t compteur_bmp;
    uint32_t anim_ultime;
    uint32_t en_ultime;
    Mix_Chunk *wav_catch[2];

    uint32_t ultime_timer;
    uint32_t pwrup_timer;
    uint32_t PwrUP_id;
} Player;

Player* init_player(uint32_t nb_player, uint8_t num, char *lib, uint32_t pos[2][nb_player], char *filename);
void link_player(Player *player, char *lib);
void get_name_and_lib_sizes(char *filename, uint8_t num, uint32_t sizes[2]);
void get_name_and_lib(char *filename, Player *player);
void init_player_pos(uint32_t nb_player, uint32_t pos[2][nb_player]);
SDL_Color init_player_color(uint8_t num);
void players_toString(Player **players, uint8_t nb_players);

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
