#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "actions.h"

void err(char *msg);
void handle_client(int accept_sd, struct sockaddr_in addrcli, int i);
void server();

#endif //SERVER_H
