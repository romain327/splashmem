#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"


uint32_t colors[MAX_PLAYERS+1] = { 0 };

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void init_colors(SDL_PixelFormat *format)
{
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00);
    colors[1] = SDL_MapRGB(format, 0xFF, 0, 0);
    colors[2] = SDL_MapRGB(format, 0, 0xFF, 0);
    colors[3] = SDL_MapRGB(format, 0, 0x0, 0xFF);
    colors[4] = SDL_MapRGB(format, 0xFF, 0, 0xFF);
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void inits(int argc, char *argv[])
{
    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);
    SDL_PixelFormat *format = screenSurface->format;
    init_colors(format);
	world_create_players();

    actions_init(argc, argv);

    printf("inits done\n");
}