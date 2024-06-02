#include "renderer.h"

void renderMap(SDL_Renderer *renderer, Cell map[MAP_SIZE][MAP_SIZE]) {
    printf("rendering map\n");
    for(int x = 0; x<MAP_SIZE; x++) {
        for(int y = 0; y<MAP_SIZE; y++) {
            printf("rendering cell\n");
            SDL_SetRenderDrawColor(renderer, map[x][y].color.r, map[x][y].color.g, map[x][y].color.b, map[x][y].color.a);
            SDL_Rect rect = map[x][y].rect;
            rect.x = x * CELL_SIZE;
            rect.y = y * CELL_SIZE;
            printf("x : %d, y : %d, w : %d, h : %d\n", rect.x, rect.y, rect.w, rect.h);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, char *str[], SDL_Color color, SDL_Rect *textRect[], uint32_t nb_players) {
    printf("getting surface dim\n");
    for(uint32_t i = 0; i < nb_players; i++) {
        //printf("i : %d\n", i);
        //printf("infos : %s\n", str[i]);
        SDL_Surface *surface = TTF_RenderText_Solid(font, str[i], color);
        if(surface == NULL) {
            fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        }

        //printf("setting rect\n");
        //printf("surface w : %d, surface h : %d\n", surface->w, surface->h);
        textRect[i]->w = surface->w;
        textRect[i]->h = surface->h;
        textRect[i]->x = INFOS_AREA_X;
        textRect[i]->y = i*surface->h;

        printf("%d\n", textRect[i]->y);
        printf("creating texture\n");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        printf("copying texture\n");

        SDL_RenderCopy(renderer, texture, NULL, textRect[i]);
        SDL_DestroyTexture(texture);

        SDL_FreeSurface(surface);
    }
    printf("rendering text done\n");
}

void render_player_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player *player) {
    map[player->x][player->y].color = player->player_color;
}

void make_text(char *str[], Player **players, uint32_t nb_players) {
    char *player_text = malloc(sizeof(char) * 100);
    for(uint8_t i = 0; i < nb_players; i++) {
        
        sprintf(player_text, "%s : credits : %d, x : %d, y : %d, score : %d\n", players[i]->lib_name, players[i]->credits, players[i]->x, players[i]->y, players[i]->score);
        printf("%s\n", player_text);
        strcpy(str[i], player_text);
    }
    free(player_text);
}

void render_bmp(SDL_Renderer *renderer, Player *player, const uint32_t nb_player) {
    uint32_t etatBmp = 0;

    SDL_Texture* TextureTemp = NULL;
    SDL_Texture* TextureTemp2 = NULL;
    SDL_Rect* player_bmp_coord = malloc(sizeof(SDL_Rect));
    SDL_Rect* player_bmp_coord2 = malloc(sizeof(SDL_Rect));

    /*****************************DeplacementJoueur***********************/

    printf("rendering bmp coord\n");
    player_bmp_coord->x = (player->x)*10 - 35;
    player_bmp_coord->y = (player->y)*10 - 35;
    player_bmp_coord->h = 75;
    player_bmp_coord->w = 80;

    printf("bmp state\n");
    if(player->x_avant > player->x)
        etatBmp = 0;

    if(player->x_avant < player->x)
        etatBmp = 1;

    if(player->y_avant > player->y)
        etatBmp = 2;

    if(player->y_avant < player->y)
        etatBmp = 3;

    printf("bmp texture\n");
    switch (etatBmp) {
    case 0:
        TextureTemp = player->bmp.bmp_gauche[player->compteur_bmp];
        break;
    case 1:
        TextureTemp = player->bmp.bmp_droit[player->compteur_bmp];
        break;
    case 2:
        TextureTemp = player->bmp.bmp_haut[player->compteur_bmp];
        break;
    case 3:
        TextureTemp = player->bmp.bmp_bas[player->compteur_bmp];
        break;
    default:
        break;
    }

    SDL_SetRenderTarget(renderer, TextureTemp);
    SDL_RenderCopy(renderer, TextureTemp, NULL, player_bmp_coord);
    SDL_SetRenderTarget(renderer, NULL);

    player->compteur_bmp = !player->compteur_bmp;

    player->x_avant = player->x;
    player->y_avant = player->y;

    /*****************************Mort***********************/
    if(player->credits == 0) {
        TextureTemp = player->bmp.bmp_mort;
    }

    /*****************************Mort***********************/
    if(player->en_ultime == 1 && player->anim_ultime != 1) {
        player_bmp_coord2->x = 400;
        player_bmp_coord2->y = 1100;

        if(player->ultime_timer == 0) {
            player_bmp_coord2->x = -1200;
            Mix_PlayChannel(-1, player->wav_catch[0], 0);
        }

        player_bmp_coord2->x += 250;
        player_bmp_coord2->y = 0;

        player->ultime_timer += 1;

        TextureTemp = player->bmp.bmp_catch[1];
        TextureTemp2 = player->bmp.bmp_catch[0];

        SDL_SetRenderTarget(renderer, TextureTemp);
        SDL_RenderCopy(renderer, TextureTemp2, NULL, player_bmp_coord2);
        SDL_SetRenderTarget(renderer, NULL);

        if(player->ultime_timer >= 8) {
            player->ultime_timer = 0;
            player->anim_ultime = 1;
            Mix_PlayChannel(-1, player->wav_catch[1], 0);
        }
    }

    if(player->ultime_timer == 1) {
        player_bmp_coord->h += 100;
        player_bmp_coord->w += 100;
        player_bmp_coord->x -= 50;
        player_bmp_coord->y -= 50;

        if(player->ultime_timer < 8) {
            TextureTemp = player->bmp.bmp_ultime[player->id - 1];
        }
        if(player->ultime_timer > 7 && player->ultime_timer < 17) {
            TextureTemp = player->bmp.bmp_ultime[7];
        }
        if(player->ultime_timer >= 16) {
            player->ultime_timer = 0;
            player->en_ultime = 0;
            player->anim_ultime = 0;
        }
        player->ultime_timer += 1;
    }

    SDL_SetRenderTarget(renderer, TextureTemp);
    SDL_RenderCopy(renderer, TextureTemp, NULL, player_bmp_coord);
    SDL_SetRenderTarget(renderer, NULL);
}