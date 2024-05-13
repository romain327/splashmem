#include "../include/handler.h"

void handle(SDL_Event *e, SDL_Renderer *renderer, SDL_Window *window) {
    switch (e->type) {
        case SDL_QUIT:
            quit(renderer, window);
            break;
        case SDLK_ESCAPE:
            quit(renderer, window);
            break;
        default:
            break;
    }
}

void quit(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}