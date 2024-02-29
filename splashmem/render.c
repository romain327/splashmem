#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"

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

        for (int i = 0; i < MAX_PLAYERS ; i++)
        {
            world_do_player_action(players[i]);
			for (int j = 0; j < MAX_PLAYERS*BOMB_COUNTER; j++)
            {
			    if (bombs[j].id_p == i+1)
                {
                    bombs[j].timer--;
                    printf("bomb %d\n", bombs[j].timer);
                    printf("bomb %d\n", bombs[j].id_b);
                    printf("bomb %d\n", bombs[j].x);
                    printf("bomb %d\n", bombs[j].y);
                    if (bombs[j].timer == 0)
                    {
                        printf("bomb explode\n");
                        explode_bomb(&bombs[j]);
                    }
                }
            }
        }
	render_map();
    render_player();
	SDL_Delay(200);
    }
}
