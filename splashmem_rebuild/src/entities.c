#include "../include/entities.h"

/***********************************************************************************/
/*                                       BOMB                                      */
/***********************************************************************************/
void init_bomb(Bomb *bomb) {
    bomb->x = 0;
    bomb->y = 0;
    bomb->timer = -1;
}

/***********************************************************************************/
/*                                     PLAYER                                      */
/***********************************************************************************/
Player *init_player(uint32_t nb_player, uint8_t num, char *lib) {
    Player *player = malloc(sizeof(Player));
    player->id = num;
    uint32_t **pos = init_player_pos(nb_player, num);
    player->x = pos[0][num-1]*10;
    player->y = pos[1][num-1]*10;
    player->p = (SDL_Rect){player->x, player->y, CELL_SIZE, CELL_SIZE};
    player->player_color = init_player_color(num);
    player->credits = CREDITS;
    player->is_done = 0;
    Bomb *bombs[BOMB_TIMER];
    for (int i = 0; i < BOMB_TIMER; i++) {
        init_bomb(bombs[i]);
    }

    link_player(player, lib);

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

void get_name_and_lib(char *filename, Player *player) {
    char *name = malloc(25);
    char *lib_name = malloc(30);
    uint32_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_ERROR);
    }
    lseek(fd, 25 + (25+30)*(player->id - 1), SEEK_SET);
    read(fd, name, 25);
    read(fd, lib_name, 30);
    lseek(fd, 0, SEEK_SET);
    close(fd);

    uint8_t i = 0;
    while (name[i] != '\0') {
        player->name[i] = name[i];
        i++;
    }
    i = 0;
    while (lib_name[i] != '\0') {
        player->lib_name[i] = lib_name[i];
        i++;
    }
}

uint32_t **init_player_pos(uint32_t nb_player, uint8_t num) {
    uint32_t **pos = malloc(2 * sizeof(uint32_t *));
    for (int i = 0; i < 2; i++) {
        pos[i] = malloc(nb_player * sizeof(uint32_t));
    }

    switch (num) {
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
    return pos;
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
    return color;
}

/***********************************************************************************/
/*                                       MAP                                       */
/***********************************************************************************/
uint32_t init_map(Cell map[MAP_SIZE][MAP_SIZE]) {
    for(int x = 0; x<MAP_SIZE; x+=CELL_SIZE) {
        for(int y = 0; y<MAP_SIZE; y+=CELL_SIZE) {
            map[x][y].x = x;
            map[x][y].y = y;
            map[x][y].color = (SDL_Color){0, 0, 0, 255};
            map[x][y].rect = (SDL_Rect){x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE};
        }
    }
    return EXIT_SUCCESS;
}

uint32_t init_player_pos_on_map(Cell map[MAP_SIZE][MAP_SIZE], Player **players, uint32_t nb_player) {
    uint32_t map_x;
    uint32_t map_y;

    for(int i = 0; i < nb_player; i++) {
        map_x = players[i]->x;
        map_y = players[i]->y;
        map[map_x][map_y].color = players[i]->player_color;
    }
    return EXIT_SUCCESS;
}

uint32_t compare_color(SDL_Color c1, SDL_Color c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

void update_score(Player **players, Cell map[MAP_SIZE][MAP_SIZE], uint32_t nb_player) {
    for(int x = 0; x<MAP_SIZE; x+=CELL_SIZE) {
        for(int y = 0; y<MAP_SIZE; y+=CELL_SIZE) {
            for (uint32_t i = 0; i < nb_player; i++) {
                if (compare_color(map[x][y].color, players[i]->player_color)) {
                    players[i]->score++;
                }
            }
        }
    }
}