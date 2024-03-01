#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int port_num = 2000;
const int maxlength = 256;

void err(char s[]) {
    perror(s);
    exit(EXIT_FAILURE);
}

void handle_client(int accept_sd, struct sockaddr_in addrcli) {
    char msg[maxlength];
    char replymsg[maxlength];

    while (1) {
        int ret = recvfrom(accept_sd, msg, maxlength, 0, NULL, NULL);
        if (ret == -1) {
            err("recvfrom");
            break;
        } else if (ret == 0) {
            printf("Client déconnecté (port = %d)\n", ntohs(addrcli.sin_port));
            break;
        } else {
            msg[ret] = '\0';
            printf("Client (port = %d) dit : %s\n", ntohs(addrcli.sin_port), msg);

            // prépare et envoie une réponse
            snprintf(replymsg, maxlength, "J'ai bien reçu '%s'", msg);
            ret = sendto(accept_sd, replymsg, strlen(replymsg), 0, (const struct sockaddr*)&addrcli, sizeof(addrcli));
            if (ret == -1) {
                err("sendto");
                break;
            }
        }
    }

    close(accept_sd);
}

int main() {
    int sd;
    struct sockaddr_in addrsrv;
    struct sockaddr_in addrcli;
    socklen_t len_addrcli = sizeof(addrcli);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        err("création socket");
    }

    addrsrv.sin_family = AF_INET;
    addrsrv.sin_port = htons(port_num);
    addrsrv.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (const struct sockaddr*)&addrsrv, sizeof(addrsrv)) != 0) {
        err("bind");
    }

    listen(sd, 5);

    printf("Serveur en attente de connexions sur le port %d\n", port_num);

    while (1) {
        int accept_sd = accept(sd, (struct sockaddr*)&addrcli, &len_addrcli);
        if (accept_sd == -1) {
            err("accept");
        }

        printf("Nouvelle connexion acceptée (port = %d)\n", ntohs(addrcli.sin_port));

        // Crée un processus pour gérer la nouvelle connexion
        pid_t child_pid = fork();

        if (child_pid == -1) {
            err("fork");
        } else if (child_pid == 0) {
            // Dans le processus enfant, ferme le socket d'écoute
            close(sd);
            handle_client(accept_sd, addrcli);
            exit(EXIT_SUCCESS);
        } else {
            // Dans le processus parent, ferme le socket de la connexion acceptée
            close(accept_sd);
        }
    }

    return 0;
}
