#ifndef SPLASHMEM2_HANDLE_H
#define SPLASHMEM2_HANDLE_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>

void handle(SDL_Event *e, SDL_Renderer *renderer, SDL_Window *window);
void quit(SDL_Renderer *renderer, SDL_Window *window);
#endif //SPLASHMEM2_HANDLE_H
