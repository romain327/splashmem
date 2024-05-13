CC = gcc
CFLAGS = -Wall -g2

SRCDIR = src
INC = /home/romain/Bureau/Info/Projets/splashmem/splashmem_rebuild_v2/include
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)
EXE = splashmem

LDFLAGS = -lSDL2 -ldl

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -I$(INC) $(OBJS) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $<
	mv *.o $(SRCDIR)