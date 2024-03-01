#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "param.h"
#include "player.h"
#include "actions.h"




/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
t_player* players[MAX_PLAYERS] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players()
{
    int i = 0;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        players[i] = (t_player*) malloc(sizeof(t_player));
        player_init(players[i], i);
        world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_do_player_action(t_player *p_player)
{
    char act = p_player->get_action();
    actions_do(p_player, act);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_paint_spot(uint32_t x, uint32_t y, uint32_t num)
{
    uint32_t pos = y * MAP_SIZE + x;
    mapmem[pos] = num;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_get_winner()
{
    int colors[MAX_PLAYERS] = {0};
    for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
    {
        if (mapmem[i] != 0)
        {
            colors[mapmem[i] - 1]++;
        }
    }
    int max = colors[0];
    int winner = 1;
    for (int i = 1; i < MAX_PLAYERS; i++)
    {
        if (colors[i] > max)
        {
            max = colors[i];
            winner = i + 1;
        }
    }
    printf("Player %d wins\n", winner);
}
