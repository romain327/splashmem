#include "inits.h"

uint32_t init(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *grid, SDL_Color color, uint32_t nb_player, char *argv[], Player **players, Cell map[MAP_SIZE][MAP_SIZE], char *game_master) {
    uint32_t window_success = init_window(window, renderer);
    uint32_t grid_success = init_grid_texture(renderer, grid, color);

    for (uint8_t i = 0; i < nb_player; i++) {
        players[i] = init_player(nb_player, i+1, argv[i+2]);
    }

    uint32_t map_success = init_map(map);
    uint32_t position_success = init_player_pos_on_map(map, players, nb_player);
    uint32_t game_master_success = init_game_master(argv[1], game_master);
    if (window_success == EXIT_ERROR || grid_success == EXIT_ERROR || map_success == EXIT_ERROR || position_success == EXIT_ERROR || game_master_success == EXIT_ERROR) {
        return EXIT_ERROR;
    }

    return EXIT_SUCCESS;
}

uint32_t init_window(SDL_Window *window, SDL_Renderer *renderer) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_ERROR;
    }

    if(SDL_CreateWindowAndRenderer(VIEWPORT_W, VIEWPORT_H, SDL_WINDOW_SHOWN, &window, &renderer) != 0) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
        return EXIT_ERROR;
    }

    return EXIT_SUCCESS;
}

void set_color(SDL_Renderer *renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

uint32_t init_grid_texture(SDL_Renderer *renderer, SDL_Texture *grid, SDL_Color color) {
    grid = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, VIEWPORT_W, VIEWPORT_W);
    if(grid == NULL) {
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        return EXIT_ERROR;
    }

    SDL_SetRenderTarget(renderer, grid);
    set_color(renderer, color);
    for(uint32_t x = 0; x< MAP_SIZE; x++) {
        SDL_RenderDrawLine(renderer, x*CELL_SIZE, 0, x*CELL_SIZE, VIEWPORT_W);
    }

    for(uint32_t y = 0; y< MAP_SIZE; y++) {
        SDL_RenderDrawLine(renderer, 0, y*CELL_SIZE, VIEWPORT_W, y*CELL_SIZE);
    }

    SDL_SetRenderTarget(renderer, NULL);

    return EXIT_SUCCESS;
}

uint32_t init_game_master(char *filename, char *game_master) {
    char *temp = malloc(25);

    uint32_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_ERROR;
    }
    read(fd, temp, 25);
    close(fd);

    uint8_t i = 0;
    while (temp[i] != '\0') {
        game_master[i] = temp[i];
        i++;
    }

    return EXIT_SUCCESS;
}