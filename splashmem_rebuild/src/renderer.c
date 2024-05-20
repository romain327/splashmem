#include "renderer.h"

void renderMap(SDL_Renderer *renderer, Cell map[MAP_SIZE][MAP_SIZE]) {
    for(int x = 0; x<MAP_SIZE; x+=CELL_SIZE) {
        for(int y = 0; y<MAP_SIZE; y+=CELL_SIZE) {
            SDL_SetRenderDrawColor(renderer, map[x][y].color.r, map[x][y].color.g, map[x][y].color.b, map[x][y].color.a);
            SDL_RenderFillRect(renderer, &map[x][y].rect);
        }
    }
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *str, SDL_Rect *rect, SDL_Color color) {
    printf("getting surface dim\n");
    SDL_Surface *surface = TTF_RenderText_Solid(font, str, color);
    if(surface == NULL) {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }

    printf("setting rect\n");
    printf("surface w : %d, surface h : %d\n", surface->w, surface->h);
    rect->w = surface->w;
    rect->h = surface->h;
    printf("creating texture\n");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    printf("copying texture\n");
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render_player_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player *player) {
    map[player->x][player->y].color = player->player_color;
}

void make_text(char *text, Player **players, uint8_t nb_players) {
    char *player_text;
    for(uint8_t i = 0; i < nb_players; i++) {
        player_text = malloc(78);
        sprintf(player_text, "%s : credits : %d, x : %d, y : %d, score : %d\n", players[i]->lib_name, players[i]->credits, players[i]->x, players[i]->y, players[i]->score);
        printf("%s\n", player_text);
        strcat(text, player_text);
    }
    strncat(text, "\0", 1);
    free(player_text);
}