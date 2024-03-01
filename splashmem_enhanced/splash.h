#ifndef __SPALSH__
#define __SPLASH__

#include "param.h"

extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern uint32_t colors[];
extern int quitting;


void init_colors(SDL_PixelFormat *format);
void inits(int argc, char *argv[]);
void main_loop(char *shared_memory, pid_t pid);

#endif 