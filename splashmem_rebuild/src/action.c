#include "action.h"

void action_do(Player *player, Cell map[MAP_SIZE][MAP_SIZE], char act) {
    uint32_t on_border;
    switch(act) {
        case ACTION_STILL:
            break;
        case ACTION_MOVE_L:
            on_border = check_border(DIR_LEFT, player->x, MOVE);
            if(check_credits(player, MOVE)) {
                move_left(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_MOVE_R:
            on_border = check_border(DIR_RIGHT, player->x, MOVE);
            if(check_credits(player, MOVE)) {
                move_right(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_MOVE_U:
            on_border = check_border(DIR_UP, player->y, MOVE);
            if(check_credits(player, MOVE)) {
                move_up(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_MOVE_D:
            on_border = check_border(DIR_DOWN, player->y, MOVE);
            if(check_credits(player, MOVE)) {
                move_down(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_DASH_L:
            on_border = check_border(DIR_LEFT, player->x, DASH);
            printf("on_border : %d\n", on_border);
            if(check_credits(player, DASH)) {
                dash_left(player, map, on_border);
            }
            break;
        case ACTION_DASH_R:
            on_border = check_border(DIR_RIGHT, player->x, DASH);
            if(check_credits(player, DASH)) {
                dash_right(player, map, on_border);
            }
            break;
        case ACTION_DASH_U:
            on_border = check_border(DIR_UP, player->y, DASH);
            if(check_credits(player, DASH)) {
                dash_up(player, map, on_border);
            }
            break;
        case ACTION_DASH_D:
            on_border = check_border(DIR_DOWN, player->y, DASH);
            if(check_credits(player, DASH)) {
                dash_down(player, map, on_border);
            }
            break;
        case ACTION_TELEPORT_L:
            on_border = check_border(DIR_LEFT, player->x, TELEPORT);
            if(check_credits(player, TELEPORT)) {
                teleport_left(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_TELEPORT_R:
            on_border = check_border(DIR_RIGHT, player->x, TELEPORT);
            if(check_credits(player, TELEPORT)) {
                teleport_right(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_TELEPORT_U:
            on_border = check_border(DIR_UP, player->y, TELEPORT);
            if(check_credits(player, TELEPORT)) {
                teleport_up(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_TELEPORT_D:
            on_border = check_border(DIR_DOWN, player->y, TELEPORT);
            if(check_credits(player, TELEPORT)) {
                teleport_down(player, on_border);
            }
            render_player_on_map(map, player);
            break;
        case ACTION_SPLASH:
            if(check_credits(player, SPLASH)) {
                splash(map, player);
            }
            break;
        case ACTION_BOMB:
            if(check_credits(player, BOMB)) {
                drop_bomb(player);
            }
        case ACTION_NUMBER:
            break;
    }
}

uint8_t check_border(enum direction dir, uint32_t pos, uint32_t move) {
    for(int i = 0; i < move; i++) {
        if(dir == DIR_LEFT || dir == DIR_UP) {
            pos -= i;
            if(pos == 0) {
                return i;
            }
        }
        else {
            pos += i;
            if(pos == MAP_SIZE) {
                return i;
            }
        }
    }
    return move;
}

uint8_t check_border_splash(enum direction dir, uint32_t pos) {
    if(dir == DIR_LEFT || dir == DIR_UP) {
        if(pos == 0) {
            return 1;
        }
    }
    else {
        if(pos == MAP_SIZE) {
            return 1;
        }
    }
    return 0;
}

uint8_t check_credits(Player *player, uint32_t move) {
    if(player->credits == 0 || player->credits < move) {
        return 0;
    }
    return 1;
}

void move_left(Player *player, uint8_t on_border) {
    if(on_border == MOVE) {
        player->x -= MOVE;
    }
    else {
        player->x += MAP_SIZE;
        player->x -= MOVE-on_border;
    }
}

void move_right(Player *player, uint8_t on_border) {
    if(on_border == MOVE) {
        player->x += MOVE;
    }
    else {
        player->x -= MAP_SIZE;
        player->x += MOVE-on_border;
    }
}

void move_up(Player *player, uint8_t on_border) {
    if(on_border == MOVE) {
        player->y -= MOVE;
    }
    else {
        player->y += MAP_SIZE;
        player->y -= MOVE-on_border;
    }
}

void move_down(Player *player, uint8_t on_border) {
    if(on_border == MOVE) {
        player->y += MOVE;
    }
    else {
        player->y -= MAP_SIZE;
        player->y += MOVE-on_border;
    }
}

void dash_left(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border) {
    if(on_border == DASH) {
        for(uint8_t i = 0; i < DASH; i++) {
            player->x -= 1;
            render_player_on_map(map, player);
        }
    }
    else {
        for(uint8_t i = DASH-on_border; i < DASH; i++) {
            player->x -= 1;
            render_player_on_map(map, player);
        }
        player->x += MAP_SIZE;
        for(uint8_t i = 0; i < on_border; i++) {
            player->x -= 1;
            render_player_on_map(map, player);
        }
    }
}

void dash_right(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border) {
    if(on_border == DASH) {
        for(uint8_t i = 0; i < DASH; i++) {
            player->x += 1;
            render_player_on_map(map, player);
        }
    }
    else {
        for(uint8_t i = 0; i < DASH-on_border; i++) {
            player->x += 1;
            render_player_on_map(map, player);
        }
        player->x -= MAP_SIZE;
        for(uint8_t i = 0; i < on_border; i++) {
            player->x += 1;
            render_player_on_map(map, player);
        }
    }
}

void dash_up(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border) {
    if(on_border == DASH) {
        for(uint8_t i = 0; i < DASH; i++) {
            player->y -= 1;
            render_player_on_map(map, player);
        }
    }
    else {
        for(uint8_t i = 0; i < DASH-on_border; i++) {
            player->y -= 1;
            render_player_on_map(map, player);
        }
        player->y += MAP_SIZE;
        for(uint8_t i = 0; i < on_border; i++) {
            player->y -= 1;
            render_player_on_map(map, player);
        }
    }
}

void dash_down(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border) {
    if(on_border == DASH) {
        for(uint8_t i = 0; i < DASH; i++) {
            player->y += 1;
            render_player_on_map(map, player);
        }
    }
    else {
        for(uint8_t i = 0; i < DASH-on_border; i++) {
            player->y += 1;
            render_player_on_map(map, player);
        }
        player->y -= MAP_SIZE;
        for(uint8_t i = 0; i < on_border; i++) {
            player->y += 1;
            render_player_on_map(map, player);
        }
    }
}

void teleport_left(Player *player, uint8_t on_border) {
    if(on_border == TELEPORT) {
        player->x -= TELEPORT;
    }
    else {
        player->x = MAP_SIZE - TELEPORT + on_border;
    }
}

void teleport_right(Player *player, uint8_t on_border) {
    if(on_border == TELEPORT) {
        player->x += TELEPORT;
    }
    else {
        player->x = TELEPORT - on_border;
    }
}

void teleport_up(Player *player, uint8_t on_border) {
    if(on_border == TELEPORT) {
        player->y -= TELEPORT;
    }
    else {
        player->y = MAP_SIZE - TELEPORT + on_border;
    }
}

void teleport_down(Player *player, uint8_t on_border) {
    if(on_border == TELEPORT) {
        player->y += TELEPORT;
    }
    else {
        player->y = TELEPORT - on_border;
    }
}

void splash(Cell map[MAP_SIZE][MAP_SIZE], Player *player) {
    uint8_t on_border[4] = {check_border_splash(DIR_LEFT, player->x), check_border_splash(DIR_RIGHT, player->x),check_border_splash(DIR_UP, player->y), check_border_splash(DIR_DOWN, player->y)};
    if(on_border[0]) {
        player->x = MAP_SIZE-1;
    }
    else {
        player->x -= MOVE;
    }
    render_player_on_map(map, player);
    if(on_border[2]) {
        player->y = MAP_SIZE-1;
    }
    else {
        player->x -= MOVE;
    }
    render_player_on_map(map, player);
    if(on_border[1]) {
        player->x = 0;
    }
    else {
        player->x += MOVE;
    }
    render_player_on_map(map, player);
    if(on_border[3]) {
        player->y = 0;
    }
    else {
        player->y += MOVE;
    }
    render_player_on_map(map, player);
}

void drop_bomb(Player *player) {
    uint8_t i = 0;
    uint8_t dropped = 0;
    while(i < BOMB_TIMER && !dropped) {
        if(player->bombs[i]->timer == -1) {
            player->bombs[i]->x = player->x;
            player->bombs[i]->y = player->y;
            player->bombs[i]->timer = BOMB_TIMER;
            dropped = 1;
        }
        i++;
    }
}

void check_bombs(Cell map[MAP_SIZE][MAP_SIZE], Player *player) {
    for(uint8_t i = 0; i < BOMB_TIMER; i++) {
        if(player->bombs[i]->timer == 0) {
            explode_bomb(player->bombs[i], *player, map);
            init_bomb(player->bombs[i]);
        }
        else if (player->bombs[i]->timer > 0) {
            player->bombs[i]->timer--;
        }
    }
}

void explode_bomb(Bomb *bomb, Player player, Cell map[MAP_SIZE][MAP_SIZE]) {
    uint32_t x = player.x;
    uint32_t y = player.y;
    player.x = bomb->x;
    player.y = bomb->y;
    action_do(&player, map, ACTION_SPLASH);
    player.x = x;
    player.y = y;
}