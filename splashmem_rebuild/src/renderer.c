#include "../include/renderer.h"

void renderMap(SDL_Renderer *renderer, Cell map[MAP_SIZE][MAP_SIZE]) {
    for(int x = 0; x<MAP_SIZE; x+=CELL_SIZE) {
        for(int y = 0; y<MAP_SIZE; y+=CELL_SIZE) {
            SDL_SetRenderDrawColor(renderer, map[x][y].color.r, map[x][y].color.g, map[x][y].color.b, map[x][y].color.a);
            SDL_RenderFillRect(renderer, &map[x][y].rect);
        }
    }
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, char *str, SDL_Rect *rect) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, str, color);
    rect->w = surface->w;
    rect->h = surface->h;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render_player_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player *player) {
    map[player->x][player->y].color = player->player_color;
}

void make_text(char *text, Player **players, uint8_t nb_players) {
    for(uint8_t i = 0; i < nb_players; i++) {
        sprintf(text, "%s : credits : %d, x : %d, y : %d, score : %d\n", players[i]->lib_name, players[i]->credits, players[i]->x, players[i]->y, players[i]->score);
    }
}