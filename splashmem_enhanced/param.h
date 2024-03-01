#ifndef __PARAM__
#define __PARAM__

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_PLAYERS 4
#define MAP_SIZE 100
#define SPOT_NUM MAP_SIZE * MAP_SIZE
#define SQUARE_SIZE 10
#define WIN_SIZE MAP_SIZE * SQUARE_SIZE

#define P_CREDITS 9000
#define BOMB_COUNTER 5

#define PORT_NUM 2000
#define MAXLENGTH 256

#endif //__PARAM__