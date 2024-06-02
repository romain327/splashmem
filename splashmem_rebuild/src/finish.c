#include "finish.h"

void get_winner(Player **players, uint32_t nb_player) {
    uint32_t results[nb_player];
    for (uint32_t i = 0; i < nb_player; i++) {
        results[i] = players[i]->score;
    }
    uint32_t pl = 0;

    for(uint32_t i = 1; i<nb_player; i++) {
        if(results[i-1] > results[i]) {
            pl = i-1;
        }
    }
    printf("The winner is %s with %d points\n", players[pl]->name, players[pl]->score);
}

uint32_t make_file(Player **players, uint32_t nb_player, char *game_master) {
    uint32_t fd = open("results.csv", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_ERROR;
    }
    char *temp = malloc(sizeof(game_master) + 1);
    strcpy(temp, game_master);
    strcat(temp, "\n");
    write(fd, temp, strlen(temp));
    free(temp);
    for(uint32_t i = 0; i < nb_player; i++) {
        char *name = malloc(sizeof(players[i]->name) + sizeof(players[i]->lib_name) + sizeof(players[i]->score + 3));
        strcpy(name, players[i]->name);
        strcat(name, ";");
        strcat(name, players[i]->lib_name);
        strcat(name, ";");
        char *score = malloc(sizeof(players[i]->score) + 1);
        sprintf(score, "%d", players[i]->score);
        strcat(name, score);
        strcat(name, "\n");
        write(fd, name, strlen(name));
        free(name);
    }
    return EXIT_SUCCESS;
}

void send_results() {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://brouard.dev/splashmem/get_result.php");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "results.csv");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
}

void clean_and_quit(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *grid, Player **players, uint32_t nb_player) {
    for(uint32_t i = 0; i < nb_player; i++) {
        free(players[i]->name);
        free(players[i]->lib_name);
        free(players[i]);
    }
    free(players);

    SDL_DestroyTexture(grid);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}