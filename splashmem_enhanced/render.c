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
void main_loop(char *shared_memory, pid_t pid)
{
    while (!quitting)
    {
        while (finish < MAX_PLAYERS && !quitting) {

			SDL_Event event;

        	while (SDL_PollEvent(&event))
        	{
            	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
            	{
                	quitting = 1;
            	}
        	}
            for (int i = 0; i < MAX_PLAYERS ; i++)
            {
                if (players[i]->credits > 0)
                {
                    printf("%c\n", shared_memory[i]);
                    world_do_player_action(players[i], shared_memory[i]);
                    shared_memory[i] = '0';
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
	quitting = 1;
    }
	world_get_winner();
    SDL_Quit();
    kill(pid, SIGTERM);
}
