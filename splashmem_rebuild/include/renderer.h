#ifndef SPLASHMEM_RENDERER_H
#define SPLASHMEM_RENDERER_H

#include "entities.h"

void renderMap(SDL_Renderer *renderer, Cell map[MAP_SIZE][MAP_SIZE]);
void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *str, SDL_Rect *rect, SDL_Color color);
void render_player_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player *player);
void make_text(char *text, Player **players, uint8_t nb_players);

#endif //SPLASHMEM_RENDERER_H
