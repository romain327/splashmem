#include "player.h"

Player *init_player(uint32_t nb_player, uint8_t num, char *lib) {
    Player *player = malloc(sizeof(Player));
    player->id = num;
    uint32_t **pos = init_player_pos(nb_player, num);
    player->x = pos[0][num-1];
    player->y = pos[1][num-1];
    player->p = (SDL_Rect){player->x, player->y, PIXEL_SIZE, PIXEL_SIZE};
    player->color = init_colors(num);
    player->credits = CREDITS;
    player->last_bomb = 0;
    player->bomb_drop = 0;
    player->is_done = 0;

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
