#ifndef SPLASHMEM_ACTION_H
#define SPLASHMEM_ACTION_H

#include <stdint.h>
#include "params.h"
#include "entities.h"
#include "renderer.h"

#define MOVE 1
#define DASH 8
#define TELEPORT 8
#define BOMB 8
#define SPLASH 9

enum action {
    ACTION_STILL,
    ACTION_MOVE_L,
    ACTION_MOVE_R,
    ACTION_MOVE_U,
    ACTION_MOVE_D,
    ACTION_DASH_L,
    ACTION_DASH_R,
    ACTION_DASH_U,
    ACTION_DASH_D,
    ACTION_TELEPORT_L,
    ACTION_TELEPORT_R,
    ACTION_TELEPORT_U,
    ACTION_TELEPORT_D,
    ACTION_SPLASH,
    ACTION_BOMB,
    ACTION_NUMBER
};

enum direction {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
};

void action_do(Player *player, Cell map[MAP_SIZE][MAP_SIZE], char act);

uint8_t check_border(enum direction dir, uint32_t pos, uint32_t move);
uint8_t check_border_splash(enum direction dir, uint32_t pos);
uint8_t check_credits(Player *player, uint32_t move);
void move_left(Player *player, uint8_t on_border);
void move_right(Player *player, uint8_t on_border);
void move_up(Player *player, uint8_t on_border);
void move_down(Player *player, uint8_t on_border);
void dash_left(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border);
void dash_right(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border);
void dash_up(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border);
void dash_down(Player *player, Cell map[MAP_SIZE][MAP_SIZE], uint8_t on_border);
void teleport_left(Player *player, uint8_t on_border);
void teleport_right(Player *player, uint8_t on_border);
void teleport_up(Player *player, uint8_t on_border);
void teleport_down(Player *player, uint8_t on_border);
void splash(Cell map[MAP_SIZE][MAP_SIZE], Player *player);
void drop_bomb(Player *player);
void check_bombs(Cell map[MAP_SIZE][MAP_SIZE], Player *player);
void explode_bomb(Bomb *bomb, Player player, Cell map[MAP_SIZE][MAP_SIZE]);

#endif //SPLASHMEM_ACTION_H
