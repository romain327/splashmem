CC = gcc
CFLAGS = -Wall -g2

SRCDIR = src
INC = include
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)
EXE = splashmem

LDFLAGS = `sdl2-config --libs --cflags` -lSDL2_ttf -lcurl

all: $(EXE)

$(EXE): $(OBJS)
	mv *.o $(SRCDIR)
	$(CC) $(CFLAGS) -I$(INC) $(OBJS) $(LDFLAGS) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $<

clean:
	rm -f $(SRCDIR)/*.o $(EXE)
