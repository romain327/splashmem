#include "main.h"

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    SDL_Window **window = malloc(sizeof(SDL_Window *));
    SDL_Renderer **renderer = malloc(sizeof(SDL_Renderer *));
    SDL_Texture *grid = NULL;
    SDL_Color background = {0, 0, 0, 255};
    SDL_Color grid_color = {255, 255, 255, 255};

    uint32_t nb_player = argc-2;

    char *game_master = malloc(get_master_size(argv[1]));
    Player *players[nb_player];
    Cell map[MAP_SIZE][MAP_SIZE];
    uint32_t pos[2][nb_player];

    if(init(window, renderer, grid, grid_color, nb_player, argv, players, map, game_master, pos) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    SDL_SetWindowTitle(*window, "Splashmem");

    printf("TTF init\n");
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if(font == NULL) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        return EXIT_ERROR;
    }
    SDL_Rect textRect = {0, VIEWPORT_H - TEXT_AREA_H, 0, 0};
    char *text = malloc(78*nb_player + 1);
    printf("TTF init successful\n");

    uint8_t finishing = 1;
    uint8_t done = 0;
    uint32_t loop = 0;

    printf("rendering map\n");
    renderMap(*renderer, map);
    printf("making text\n");
    make_text(text, players, nb_player);
    printf("rendering text\n");
    renderText(*renderer, font, text, &textRect, grid_color);
    free(text);

    printf("starting game loop\n");
    while(finishing) {
        printf("loop %d\n", loop);
        loop++;
        printf("loop\n");
        SDL_Event e;

        SDL_RenderClear(*renderer);
        SDL_RenderCopy(*renderer, grid, NULL, NULL);

        printf("polling event\n");
        while(SDL_PollEvent(&e))
            handle(&e, *renderer, *window);

        printf("doing actions\n");
        for(uint8_t i = 0; i < nb_player; i++) {
            if(players[i]->credits > 0) {
                printf("doing action for player %d\n", i);
                action_do(players[i], map, players[i]->get_action());
            }
            else {
                players[i]->is_done = 1;
                done++;
            }
            printf("checking bombs\n");
            bombs_toString(players[i]->bombs);
            check_bombs(map, players[i]);
        }
        printf("rendering map\n");
        renderMap(*renderer, map);
        printf("updating score\n");
        update_score(players, map, nb_player);
        char *text = malloc(78*nb_player + 1);
        printf("making text\n");
        make_text(text, players, nb_player);
        printf("rendering text\n");
        renderText(*renderer, font, text, &textRect, grid_color);
        free(text);
        SDL_Delay(REFRESH_RATE);
        if(done == nb_player) {
            finishing = 0;
        }
    }
    get_winner(players, nb_player);
    if(make_file(players, nb_player, game_master)) {
        send_results();
    }

    clean_and_quit(*window, *renderer, grid, players, nb_player);
    return EXIT_SUCCESS;
}