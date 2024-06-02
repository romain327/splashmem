#ifndef SPLASHMEM_RENDERER_H
#define SPLASHMEM_RENDERER_H

#include "entities.h"

void renderMap(SDL_Renderer *renderer, Cell map[MAP_SIZE][MAP_SIZE]);
void renderText(SDL_Renderer *renderer, TTF_Font *font, char *str[], SDL_Color color, SDL_Rect *textRect[], uint32_t nb_players);
void render_player_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player *player);
void make_text(char *str[], Player **players, const uint32_t nb_players);
void render_bmp(SDL_Renderer *renderer, Player *player, const uint32_t nb_player);

#endif //SPLASHMEM_RENDERER_H
