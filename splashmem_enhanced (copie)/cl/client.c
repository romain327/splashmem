#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <termios.h>

const int port_num = 2000;
const int maxlength = 256;

void err(char s[]) {
    perror(s);
    exit(-1);
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int main() {
    int sd;
    struct sockaddr_in addr;

    char msg[maxlength];
    char replymsg[maxlength];

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) err("création socket");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_num);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Remplacez par l'adresse IP du serveur

    if (connect(sd, (const struct sockaddr*)&addr, sizeof(addr)) == -1) err("connect");

    int encore = 1;
    while (encore) {
        // saisie d'un message
        printf("Tapez sur ....  (ou 'x' pour quitter) : ");

        int car = getch();

        if (car=='x') {
            encore = 0; // Quitte la boucle si le client saisit 'exit'
        }
        else {         // envoie le message
            msg[0] = car;
            msg[1] = '\0';
            if (sendto(sd, msg, strlen(msg), 0, NULL, 0) == -1)
                err("sendto");
            else {
            // attend une réponse
            int ret = recvfrom(sd, replymsg, maxlength, 0, NULL, NULL);
            if (ret == -1) {
                err("recvfrom");
                encore = 0;
            } else if (ret == 0) {
                printf("Serveur déconnecté\n");
                encore = 0;
            } else {
                replymsg[ret] = '\0';
                printf("Réponse du serveur : %s\n", replymsg);
            }
        }
    }
    }
    close(sd);

    return 0;
}
