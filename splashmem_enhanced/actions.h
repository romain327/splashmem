#ifndef __ACTIONS__
#define __ACTIONS__

#include "player.h"
#include "param.h"
#include "world.h"
#include <dlfcn.h>
#include <stdio.h>

enum action
{
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

typedef struct s_bomb
{
    uint32_t id_p;
    uint8_t id_b;
    uint32_t color;
    uint8_t* data;
    uint32_t x;
    uint32_t y;
    uint32_t timer;
} t_bomb;

void actions_do(t_player *p_player, enum action act_id);
void actions_init(int argc, char *argv[]);
void link_player(t_player *p_player, char *path);
#endif
