#ifndef SPLASHMEM_HANDLE_H
#define SPLASHMEM_HANDLE_H

#include <stdint.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/sem.h>

void handle(SDL_Event *e, SDL_Renderer *renderer, SDL_Window *window);
void quit(SDL_Renderer *renderer, SDL_Window *window);
void wait_semaphore(int semid);
void signal_semaphore(int semid);
#endif //SPLASHMEM_HANDLE_H
