#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"

char finish = 0;

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_map()
{
    int i = 0;
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    screenSurface = SDL_GetWindowSurface(window);

    for (i = 0; i < SPOT_NUM; i++)
    {
        rect.x = (i % MAP_SIZE) * SQUARE_SIZE;
        rect.y = (i / MAP_SIZE) * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[mapmem[i]]);
    }
    SDL_UpdateWindowSurface(window);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_player()
{
    int i = 0;
    screenSurface = SDL_GetWindowSurface(window);
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        rect.x = players[i]->x * SQUARE_SIZE;
        rect.y = players[i]->y * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[i] - 0x00202020);
    }
    SDL_UpdateWindowSurface(window);
}

void check_bombs(int i)
{
    for (int j = 0; j < MAX_PLAYERS*BOMB_COUNTER; j++)
    {
        if (bombs[j].id_p == i+1)
        {
            bombs[j].timer--;
            if (bombs[j].timer == 0)
            {
                explode_bomb(&bombs[j]);
            }
        }
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void main_loop()
{
    // int is_game_finish = 0;   vous pouvez l'utilisez

    while (!quitting)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quitting = 1;
            }
        }
        while (finish < MAX_PLAYERS) {
            for (int i = 0; i < MAX_PLAYERS ; i++)
            {
                if (players[i]->credits > 0)
                {
                    //printf("Player %d credits: %d\n", i, players[i]->credits);
                    world_do_player_action(players[i], cmd[i]);
                    check_bombs(i);
                }
                else {
                    if (players[i]->is_done == 0)
                    {
                        players[i]->is_done = 1;
                        finish++;
                    }
                }
            }
	        render_map();
            render_player();
	        SDL_Delay(500);
        }
        for (int i = 0; i < BOMB_COUNTER; i++)
        {
            for (int j = 0; j < MAX_PLAYERS; j++)
            {
                check_bombs(j);
            }
        }

    }
    quitting = 1;
}
