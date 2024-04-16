#include "main.h"

int main(int argc, char *argv[]) {
    // setup window
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window *window = SDL_CreateWindow("Splashmem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VIEWPORT_SIZE, VIEWPORT_SIZE, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // create the render target texture
    SDL_Texture *renderTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, VIEWPORT_SIZE, VIEWPORT_SIZE);
    SDL_SetRenderTarget(renderer, renderTarget);

    // set a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect map[MAP_SIZE][MAP_SIZE];
    for(uint8_t x = 0; x<MAP_SIZE; x++) {
        for(uint8_t y = 0; y<MAP_SIZE; y++) {
            map[x][y].x = x;
            map[x][y].y = y;
            map[x][y].w = PIXEL_SIZE;
            map[x][y].h = PIXEL_SIZE;
        }
    }

    //setup the screen
    SDL_Event e;
    uint32_t time = SDL_GetTicks();

    //init players
    Player *players[argc-1];
    for(uint8_t i = 1; i<argc; i++) {
        players[i] = init_player(argc-1, i, argv[i]);
        SDL_SetRenderDrawColor(renderer, players[i-1]->color[0], players[i-1]->color[1], players[i-1]->color[2], players[i-1]->color[3]);
        SDL_RenderFillRect(renderer, &players[i-1]->p);
    }

    while(1) {
        //handling events
        while(SDL_PollEvent(&e))
            handle(&e, renderer, window);

        int32_t width;
        int32_t height;
        SDL_GetWindowSize(window, &width, &height);
        SDL_RenderPresent(renderer);

        // render the target texture to the screen
        SDL_Rect renderSize = {0, 0 , width, height};
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, renderTarget, NULL, &renderSize);

        // and set the render target back to the texture
        SDL_SetRenderTarget(renderer, renderTarget);

        // fill with black before the next loop
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //maj de la position du joueur

    }

    return EXIT_SUCCESS;
}