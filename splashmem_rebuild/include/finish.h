#ifndef SPLASHMEM_FINISH_H
#define SPLASHMEM_FINISH_H

#include <stdint.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "entities.h"

void get_winner(Player **players, uint32_t nb_player);
uint32_t make_file(Player **players, uint32_t nb_player, char *game_master);
void send_results();
void clean_and_quit(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *grid, Player **players, uint32_t nb_player);

#endif //SPLASHMEM_FINISH_H
