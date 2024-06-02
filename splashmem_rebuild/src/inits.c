#include "inits.h"

uint32_t init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture *grid, SDL_Color color, uint32_t nb_player, char *argv[], Player **players, Cell map[MAP_SIZE][MAP_SIZE], char *game_master, uint32_t pos[2][nb_player]) {
    printf("init window and renderer\n");
    uint32_t window_success = init_window(window, renderer);

    printf("init grid texture\n");
    uint32_t grid_success = init_grid_texture(*renderer, grid, color);

    printf("init player pos\n");
    init_player_pos(nb_player + 1, pos);

    for (uint8_t i = 0; i < nb_player; i++) {
        printf("init player %d\n", i);
        players[i] = init_player(nb_player, i+1, argv[i+2], pos, argv[1]);
    }

    printf("init images\n");
    uint32_t images_success = init_players_bmp(*renderer, players);

    printf("init map\n");
    uint32_t map_success = init_map(map);

    printf("init player position on map\n");
    uint32_t position_success = init_player_pos_on_map(map, players, nb_player);

    printf("players to string\n");
    players_toString(players, nb_player);

    printf("init game master\n");
    printf("%s\n", argv[1]);
    uint32_t game_master_success = init_game_master(argv[1], game_master);
    if (window_success == EXIT_ERROR || grid_success == EXIT_ERROR || map_success == EXIT_ERROR || position_success == EXIT_ERROR || game_master_success == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    printf("init successful\n");
    return EXIT_SUCCESS;
}

uint32_t init_window(SDL_Window **window, SDL_Renderer **renderer) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_ERROR;
    }

    if(SDL_CreateWindowAndRenderer(VIEWPORT_W, VIEWPORT_H, SDL_WINDOW_SHOWN, window, renderer) != 0) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
        return EXIT_ERROR;
    }
    printf("Window init successful\n");
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

    printf("Grid texture init successful\n");
    return EXIT_SUCCESS;
}

uint32_t get_master_size(char *filename) {
    printf("opening file\n");
    uint32_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_ERROR;
    }
    uint32_t size = 0;
    char c;
    while(c != '\0') {
        read(fd, &c, 1);
        size++;
    }
    lseek(fd, 0, SEEK_SET);
    close(fd);
    printf("size: %d\n", size);
    return size;
}

uint32_t init_game_master(char *filename, char *game_master) {
    printf("opening file\n");
    uint32_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_ERROR;
    }
    printf("reading file\n");
    read(fd, game_master, sizeof(game_master));
    lseek(fd, 0, SEEK_SET);
    close(fd);

    printf("Game master init successful\n");
    return EXIT_SUCCESS;
}

uint32_t init_players_bmp(SDL_Renderer *renderer, Player **players) {
    SDL_Surface* image;

    /////////////////Joueur 1////////////////

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Haut1.bmp");
    players[0]->bmp.bmp_haut[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Haut2.bmp");
    players[0]->bmp.bmp_haut[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Bas1.bmp");
    players[0]->bmp.bmp_bas[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Bas2.bmp");
    players[0]->bmp.bmp_bas[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Droite1.bmp");
    players[0]->bmp.bmp_droit[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP(".assets/images/Kevin/Kevin_Droite2.bmp");
    players[0]->bmp.bmp_droit[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Gauche1.bmp");
    players[0]->bmp.bmp_gauche[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Gauche2.bmp");
    players[0]->bmp.bmp_gauche[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Mort.bmp");
    players[0]->bmp.bmp_mort = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_1.bmp");
    players[0]->bmp.bmp_ultime[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_2.bmp");
    players[0]->bmp.bmp_ultime[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_3.bmp");
    players[0]->bmp.bmp_ultime[2] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_4.bmp");
    players[0]->bmp.bmp_ultime[3] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_5.bmp");
    players[0]->bmp.bmp_ultime[4] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_6.bmp");
    players[0]->bmp.bmp_ultime[5] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_7.bmp");
    players[0]->bmp.bmp_ultime[6] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Kevin/Kevin_Ultime/Kevin_Ultime_8.bmp");
    players[0]->bmp.bmp_ultime[7] = SDL_CreateTextureFromSurface(renderer,image);

    //////////////Joueur 2/////////////////

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Haut1.bmp");
    players[1]->bmp.bmp_haut[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Haut2.bmp");
    players[1]->bmp.bmp_haut[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Bas1.bmp");
    players[1]->bmp.bmp_bas[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Bas2.bmp");
    players[1]->bmp.bmp_bas[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Droit1.bmp");
    players[1]->bmp.bmp_droit[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Droit2.bmp");
    players[1]->bmp.bmp_droit[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Gauche1.bmp");
    players[1]->bmp.bmp_gauche[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Gauche2.bmp");
    players[1]->bmp.bmp_gauche[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Mort.bmp");
    players[1]->bmp.bmp_mort = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_1.bmp");
    players[1]->bmp.bmp_ultime[0] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_2.bmp");
    players[1]->bmp.bmp_ultime[1] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_3.bmp");
    players[1]->bmp.bmp_ultime[2] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_4.bmp");
    players[1]->bmp.bmp_ultime[3] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_5.bmp");
    players[1]->bmp.bmp_ultime[4] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_6.bmp");
    players[1]->bmp.bmp_ultime[5] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_7.bmp");
    players[1]->bmp.bmp_ultime[6] = SDL_CreateTextureFromSurface(renderer,image);

    image = SDL_LoadBMP("./assets/images/Romain/Romain_Ultime/Romain_Ultime_8.bmp");
    players[1]->bmp.bmp_ultime[7] = SDL_CreateTextureFromSurface(renderer,image);

    SDL_FreeSurface(image);

    return EXIT_SUCCESS;
}

void init_wav(Player **players, Mix_Chunk *dash, Mix_Chunk *scooby, Mix_Chunk *tetris) {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(32);

    for(uint8_t i = 0; i < 33; i++) {
        Mix_Volume(i, 128);
    }

    dash = Mix_LoadWAV("./assets/sounds/dash.wav");
    scooby = Mix_LoadWAV("./assets/sounds/scooby.wav");
    tetris = Mix_LoadWAV("./assets/sounds/tetris.wav");

    players[0]->wav_catch[0] = Mix_LoadWAV("./assets/sounds/Kevin_Catch_1.wav");
    players[0]->wav_catch[1] = Mix_LoadWAV("./assets/sounds/Kevin_Catch_2.wav");

    players[1]->wav_catch[0] = Mix_LoadWAV("./assets/sounds/Romain_Catch_1.wav");
    players[1]->wav_catch[1] = Mix_LoadWAV("./assets/sounds/Romain_Catch_2.wav");

    Mix_PlayChannel(1, tetris, -1);
}
