CC = gcc
DB = gdb
CFLAGS = -Wall -g2

SRCDIR = src
INC = include
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)
EXE = splashmem
ARGS = game_config.bin libs/p1.so libs/p2.so

LDFLAGS = `sdl2-config --libs --cflags` -lSDL2_ttf -lcurl

all: $(EXE)

$(EXE): $(OBJS)
	mv *.o $(SRCDIR)
	$(CC) $(CFLAGS) -I$(INC) $(OBJS) $(LDFLAGS) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $<

clean:
	rm -f $(SRCDIR)/*.o $(EXE)

debug: $(EXE)
	$(DB) $(EXE) $(ARGS)

run:
	./$(EXE) $(ARGS)