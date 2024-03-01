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
char buffer[MAX_PLAYERS];
short ports[MAX_PLAYERS] = {0};
int connections;
char cmd;
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

void handle_client(int accept_sd, struct sockaddr_in addrcli) {
    char msg[MAXLENGTH];
    char replymsg[MAXLENGTH];

    while (1) {
        int ret = recvfrom(accept_sd, msg, MAXLENGTH, 0, NULL, NULL);
        if (ret == -1) {
            err("recvfrom");
            break;
        } else if (ret == 0) {
            printf("Client déconnecté (port = %d)\n", ntohs(addrcli.sin_port));
            break;
        } else {
            msg[ret] = '\0';
            printf("Client (port = %d) dit : %s\n", ntohs(addrcli.sin_port), msg);

            //snprintf(replymsg, MAXLENGTH, "J'ai bien reçu '%s'", msg);
            ret = sendto(accept_sd, replymsg, strlen(replymsg), 0, (const struct sockaddr*)&addrcli, sizeof(addrcli));
            if (ret == -1) {
                err("sendto");
                break;
            }
			buffer[connections] = msg[0];
        }
    }

    close(accept_sd);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void main_loop(struct sockaddr_in addrcli, socklen_t len_addrcli, int sd)
{

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
	}
        while (finish < MAX_PLAYERS) {

        	int accept_sd = accept(sd, (struct sockaddr*)&addrcli, &len_addrcli);
        	if (accept_sd == -1) {
            	err("accept");
        	}

        	printf("Nouvelle connexion acceptée (port = %d)\n", ntohs(addrcli.sin_port));
			ports[connections] = ntohs(addrcli.sin_port);
			connections++;

        	pid_t child_pid = fork();

        	if (child_pid == -1) {
            	err("fork");
        	} else if (child_pid == 0) {
            	close(sd);
            	handle_client(accept_sd, addrcli);
            	exit(EXIT_SUCCESS);
        	} else {
            	close(accept_sd);
        	}

            for (int i = 0; i < MAX_PLAYERS ; i++)
            {
                if (ports[i] != 0)
                {

                    if (players[i]->credits > 0 )
                    {
					    cmd = buffer[i];
                        printf("Player %d credits: %d\n", i+1, players[i]->credits);
                        world_do_player_action(players[i], cmd);
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
            }
	        render_map();
            render_player();
	        SDL_Delay(5);
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
