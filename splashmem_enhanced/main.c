#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"
#include "server.h"

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

	int shmid;

	shmid = shmget(IPC_PRIVATE, 4*sizeof(char), IPC_CREAT | 0666);
	char *shared_memory = (char *) shmat(shmid, NULL, 0);

	for(int i = 0; i < MAX_PLAYERS; i++)
    {
	        shared_memory[i] = '0';
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        server(shmid);
    }

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

    inits(argc, argv);

    main_loop(shared_memory, pid);

    SDL_DelEventWatch(watch, NULL);
    SDL_DestroyWindow(window);
    SDL_Quit();

    exit(0);

} //main
