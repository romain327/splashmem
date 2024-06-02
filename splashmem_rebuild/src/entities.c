#include "entities.h"

/***********************************************************************************/
/*                                       BOMB                                      */
/***********************************************************************************/
void init_bomb(Bomb *bomb) {
    bomb->x = 0;
    bomb->y = 0;
    bomb->timer = -1;
}

void bombs_toString(Bomb *bombs[BOMB_TIMER]) {
    for(uint8_t i = 0; i < BOMB_TIMER; i++) {
        printf("bomb %d : x : %d, y : %d, timer : %d\n", i, bombs[i]->x, bombs[i]->y, bombs[i]->timer);
    }
}

/***********************************************************************************/
/*                                     PLAYER                                      */
/***********************************************************************************/
Player *init_player(uint32_t nb_player, uint8_t num, char *lib, uint32_t pos[2][nb_player], char *filename) {
    Player *player = malloc(sizeof(Player));
    player->id = num;
    player->x = pos[0][num-1];
    player->y = pos[1][num-1];
    player->x_avant = 0;
    player->y_avant = 0;
    player->compteur_bmp = 0;
    player->anim_ultime = 0;
    player->en_ultime = 0;
    player->ultime_timer = 0;
    player->pwrup_timer = 0;
    player->PwrUP_id = 0;
    player->p = (SDL_Rect){player->x, player->y, CELL_SIZE, CELL_SIZE};

    printf("init player %d color\n", num);
    player->player_color = init_player_color(num);
    player->credits = CREDITS;
    player->is_done = 0;
    player->score = 0;

    printf("init player %d bombs\n", num);
    Bomb *bombs[BOMB_TIMER];
    for (int i = 0; i < BOMB_TIMER; i++) {
        bombs[i] = malloc(sizeof(Bomb));
        init_bomb(bombs[i]);
    }
    for(int i = 0; i < BOMB_TIMER; i++) {
        player->bombs[i] = bombs[i];
    }

    printf("linking player %d\n", num);
    link_player(player, lib);

    printf("getting name and lib sizes for player %d\n", num);
    uint32_t sizes[2] = {0, 0};
    get_name_and_lib_sizes(filename, num, sizes);
    player->name = malloc(sizes[0]);
    player->lib_name = malloc(sizes[1]);

    printf("getting name and lib for player %d\n", num);
    get_name_and_lib(filename, player);

    printf("player %d init successful\n", num);
    return player;
}

void link_player(Player *player, char *lib) {
    void *handle = dlopen(lib, RTLD_LAZY);
    if (!handle)
    {
        printf("Erreur lors du chargement de la bibliothèque %s\n", lib);
        exit(EXIT_ERROR);
    }

    player->get_action = dlsym(handle, "get_action");

    if (!player->get_action)
    {
        printf("Erreur lors de la récupération de la fonction get_action pour %s\n", lib);
        dlclose(handle);
        exit(EXIT_ERROR);
    }
}

void get_name_and_lib_sizes(char *filename, uint8_t num, uint32_t sizes[2]) {
    char *name = malloc(25);
    char *lib_name = malloc(30);
    uint32_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_ERROR);
    }
    lseek(fd, 25 + (25+30)*(num - 1), SEEK_SET);
    read(fd, name, 25);
    read(fd, lib_name, 30);
    lseek(fd, 0, SEEK_SET);
    close(fd);

    while(name[sizes[0]] != '\0') {
        sizes[0]++;
    }
    while(lib_name[sizes[1]] != '\0') {
        sizes[1]++;
    }

    free(name);
    free(lib_name);
    printf("player %d name and lib sizes successful : name = %d, lib = %d\n", num, sizes[0], sizes[1]);
}

void get_name_and_lib(char *filename, Player *player) {
    printf("getting player %d name and lib\n", player->id);
    uint32_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_ERROR);
    }

    printf("reading player's name\n");
    lseek(fd, 25 + (25+30)*(player->id - 1), SEEK_SET);
    read(fd, player->name, sizeof(player->name));
    printf("reading player's lib\n");
    lseek(fd, 25 + (25+30)*(player->id - 1) + 25, SEEK_SET);
    read(fd, player->lib_name, sizeof(player->lib_name));
    lseek(fd, 0, SEEK_SET);
    close(fd);

    printf("player %d name and lib successful : %s, %s\n", player->id, player->name, player->lib_name);
}

void init_player_pos(uint32_t nb_player, uint32_t pos[2][nb_player]) {
    switch (nb_player) {
        case 1:
            pos[0][0] = MAP_SIZE/2;
            pos[1][0] = MAP_SIZE/2;
            break;
        case 2:
            pos[0][0] = MAP_SIZE/4;
            pos[0][1] = MAP_SIZE*3/4;
            pos[1][0] = MAP_SIZE/4;
            pos[1][1] = MAP_SIZE*3/4;
            break;
        case 3:
            pos[0][0] = MAP_SIZE/4;
            pos[0][1] = MAP_SIZE*3/4;
            pos[0][2] = MAP_SIZE/2;
            pos[1][0] = MAP_SIZE/4;
            pos[1][1] = MAP_SIZE*3/4;
            pos[1][2] = MAP_SIZE/4;
            break;
        case 4:
            pos[0][0] = MAP_SIZE/4;
            pos[0][1] = MAP_SIZE/4;
            pos[0][2] = MAP_SIZE*3/4;
            pos[0][3] = MAP_SIZE*3/4;
            pos[1][0] = MAP_SIZE/4;
            pos[1][1] = MAP_SIZE*3/4;
            pos[1][2] = MAP_SIZE/4;
            pos[1][3] = MAP_SIZE*3/4;
            break;
        case 5:
            pos[0][0] = MAP_SIZE/4;
            pos[0][1] = MAP_SIZE/4;
            pos[0][2] = MAP_SIZE*3/4;
            pos[0][3] = MAP_SIZE*3/4;
            pos[0][4] = MAP_SIZE/2;
            pos[1][0] = MAP_SIZE/4;
            pos[1][1] = MAP_SIZE*3/4;
            pos[1][2] = MAP_SIZE/4;
            pos[1][3] = MAP_SIZE*3/4;
            pos[1][4] = MAP_SIZE/2;
            break;
        case 6:
            pos[0][0] = MAP_SIZE/4;
            pos[0][1] = MAP_SIZE/4;
            pos[0][2] = MAP_SIZE*3/4;
            pos[0][3] = MAP_SIZE*3/4;
            pos[0][4] = MAP_SIZE/2;
            pos[0][5] = MAP_SIZE/2;
            pos[1][0] = MAP_SIZE/4;
            pos[1][1] = MAP_SIZE*3/4;
            pos[1][2] = MAP_SIZE/4;
            pos[1][3] = MAP_SIZE*3/4;
            pos[1][4] = MAP_SIZE/4;
            pos[1][5] = MAP_SIZE*3/4;
            break;
        case 7:
            pos[0][0] = MAP_SIZE/4;
            pos[0][1] = MAP_SIZE/4;
            pos[0][2] = MAP_SIZE*3/4;
            pos[0][3] = MAP_SIZE*3/4;
            pos[0][4] = MAP_SIZE/2;
            pos[0][5] = MAP_SIZE/2;
            pos[0][6] = MAP_SIZE/2;
            pos[1][0] = MAP_SIZE/4;
            pos[1][1] = MAP_SIZE*3/4;
            pos[1][2] = MAP_SIZE/4;
            pos[1][3] = MAP_SIZE*3/4;
            pos[1][4] = MAP_SIZE/4;
            pos[1][5] = MAP_SIZE*3/4;
            pos[1][6] = MAP_SIZE/2;
            break;
        case 8:
            pos[0][0] = abs(MAP_SIZE/9);
            pos[0][1] = abs(MAP_SIZE*2/9);
            pos[0][2] = abs(MAP_SIZE/3);
            pos[0][3] = abs(MAP_SIZE*4/9);
            pos[0][4] = abs(MAP_SIZE*5/9);
            pos[0][5] = abs(MAP_SIZE*2/3);
            pos[0][6] = abs(MAP_SIZE*7/9);
            pos[0][7] = abs(MAP_SIZE*8/9);
            pos[1][0] = abs(MAP_SIZE/9);
            pos[1][1] = abs(MAP_SIZE*2/9);
            pos[1][2] = abs(MAP_SIZE/3);
            pos[1][3] = abs(MAP_SIZE*4/9);
            pos[1][4] = abs(MAP_SIZE*5/9);
            pos[1][5] = abs(MAP_SIZE*2/3);
            pos[1][6] = abs(MAP_SIZE*7/9);
            pos[1][7] = abs(MAP_SIZE*8/9);
            break;
        default:
            break;
    }

    printf("init player pos successful\n");
}

SDL_Color init_player_color(uint8_t num) {
    static SDL_Color color;
    switch (num) {
        case 1:
            color.r = 255;
            color.g = 0;
            color.b = 0;
            color.a = 255;
            break;
        case 2:
            color.r = 0;
            color.g = 255;
            color.b = 0;
            color.a = 255;
            break;
        case 3:
            color.r = 0;
            color.g = 0;
            color.b = 255;
            color.a = 255;
            break;
        case 4:
            color.r = 255;
            color.g = 127;
            color.b = 0;
            color.a = 255;
            break;
        case 5:
            color.r = 127;
            color.g = 255;
            color.b = 0;
            color.a = 255;
            break;
        case 6:
            color.r = 0;
            color.g = 255;
            color.b = 255;
            color.a = 255;
            break;
        case 7:
            color.r = 255;
            color.g = 0;
            color.b = 180;
            color.a = 255;
            break;
        case 8:
            color.r = 255;
            color.g = 255;
            color.b = 0;
            color.a = 255;
            break;
        default:
            color.r = 0;
            color.g = 0;
            color.b = 0;
            color.a = 255;
    }

    printf("init player color successful\n");
    return color;
}

void players_toString(Player **players, uint8_t nb_player) {
    for(uint8_t i = 0; i < nb_player; i++) {
        printf("%s : credits : %d, x : %d, y : %d, score : %d\n", players[i]->lib_name, players[i]->credits, players[i]->x, players[i]->y, players[i]->score);
    }
}

/***********************************************************************************/
/*                                       MAP                                       */
/***********************************************************************************/
uint32_t init_map(Cell map[MAP_SIZE][MAP_SIZE]) {
    for(int x = 0; x<MAP_SIZE; x++) {
        for(int y = 0; y<MAP_SIZE; y++) {
            map[x][y].x = x;
            map[x][y].y = y;
            map[x][y].color = (SDL_Color){0, 0, 0, 255};
            map[x][y].rect = (SDL_Rect){x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE};
        }
    }

    printf("init map successful\n");
    return EXIT_SUCCESS;
}

uint32_t init_player_pos_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player **players, uint32_t nb_player) {
    uint32_t map_x;
    uint32_t map_y;

    for(uint32_t i = 0; i < nb_player; i++) {
        map_x = players[i]->x;
        map_y = players[i]->y;
        printf("%d %d\n", map_x, map_y);
        map[map_x][map_y].color = players[i]->player_color;
    }

    printf("init player position on map successful\n");
    return EXIT_SUCCESS;
}

uint32_t compare_color(SDL_Color c1, SDL_Color c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

void update_score(Player **players, Cell map[MAP_SIZE][MAP_SIZE], uint32_t nb_player) {
    for(int x = 0; x<MAP_SIZE; x++) {
        for(int y = 0; y<MAP_SIZE; y++) {
            for (uint32_t i = 0; i < nb_player; i++) {
                if (compare_color(map[x][y].color, players[i]->player_color)) {
                    players[i]->score++;
                }
            }
        }
    }
}