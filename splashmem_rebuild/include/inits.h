#ifndef SPLASHMEM_INITS_H
#define SPLASHMEM_INITS_H

#include <stdint.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Mixer.h>
#include "params.h"
#include "entities.h"

uint32_t init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture *grid, SDL_Color color, uint32_t nb_player, char *argv[], Player **players, Cell map[MAP_SIZE][MAP_SIZE], char *game_master, uint32_t pos[2][nb_player]);
uint32_t init_window(SDL_Window **window, SDL_Renderer **renderer);
void set_color(SDL_Renderer *renderer, SDL_Color color);
uint32_t init_grid_texture(SDL_Renderer *renderer, SDL_Texture *grid, SDL_Color color);
uint32_t get_master_size(char *filename);
uint32_t init_game_master(char *filename, char *game_master);
uint32_t init_players_bmp(SDL_Renderer *renderer, Player **players);
void init_wav(Mix_Chunk *dash, Mix_Chunk *scooby, Mix_Chunk *tetris);
#endif //SPLASHMEM_INITS_H
