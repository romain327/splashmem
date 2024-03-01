#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"

int quitting = 0;
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
int SDLCALL watch(void *userdata, SDL_Event *event)
{
    if (event->type == SDL_APP_WILLENTERBACKGROUND)
    {
        quitting = 1;
    }

    return 1;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    system("gcc cl/client.c -o cl/client");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SplashMem", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WIN_SIZE, WIN_SIZE,
                              SDL_WINDOW_SHOWN);
    SDL_AddEventWatch(watch, NULL);

    if (argc != 5)
    {
        printf("Wrong argument number\n");
        return 1;
    }

    int sd;
    struct sockaddr_in addrsrv;
    struct sockaddr_in addrcli;
    socklen_t len_addrcli = sizeof(addrcli);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        err("création socket");
    }

    addrsrv.sin_family = AF_INET;
    addrsrv.sin_port = htons(PORT_NUM);
    addrsrv.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (const struct sockaddr*)&addrsrv, sizeof(addrsrv)) != 0) {
        err("bind");
    }

    listen(sd, 5);

    printf("Serveur en attente de connexions sur le port %d\n", PORT_NUM);

*    inits(argc, argv);

    main_loop(addrcli, len_addrcli, sd);

    SDL_DelEventWatch(watch, NULL);
    SDL_DestroyWindow(window);
    SDL_Quit();

    exit(0);

} //main
