#include "main.h"

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *grid;
    SDL_Color background = {0, 0, 0, 255};
    SDL_Color grid_color = {255, 255, 255, 255};
    SDL_Event e;

    uint32_t nb_player = argc-2;

    char *game_master;
    Player *players[nb_player];
    Cell map[MAP_SIZE][MAP_SIZE];

    if(init(window, renderer, grid, grid_color, nb_player, argv, players, map, game_master) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    SDL_SetWindowTitle(window, "Splashmem");

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../assets/fonts/arial.ttf", 24);
    SDL_Rect textRect = {0, VIEWPORT_H - TEXT_AREA_H, TEXT_AREA_W, TEXT_AREA_H};
    char text[TEXT_AREA_W];
    uint8_t finishing = 1;
    uint8_t done = 0;
    while(finishing) {
        while(SDL_PollEvent(&e))
            handle(&e, renderer, window);

        for(uint8_t i = 0; i < nb_player; i++) {
            if(players[i]->credits > 0) {
                action_do(players[i], map, players[i]->get_action());
            }
            else {
                players[i]->is_done = 1;
                done++;
            }
            check_bombs(map, players[i]);
        }
        renderMap(renderer, map);
        update_score(players, map, nb_player);
        make_text(text, players, nb_player);
        renderText(renderer, font, text, &textRect);
        SDL_Delay(REFRESH_RATE);
        if(done == nb_player) {
            finishing = 0;
        }
    }
    get_winner(players, nb_player);
    if(make_file(players, nb_player, game_master)) {
        send_results();
    }

    clean_and_quit(window, renderer, grid, players, nb_player);
    return EXIT_SUCCESS;
}