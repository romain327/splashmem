# makefile
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CFLAGS= -Wall -g2 -fPIC  # -DDEBUG
LDFLAGS= -ldl -lSDL2
EXE=splash

players:
	cd pl && $(MAKE)

all: players $(OBJS)
	@echo $(SRCS) 
	gcc  $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(EXE)

clean_pl:
	cd pl && $(MAKE) clean

clean_all: clean 
	cd pl && $(MAKE) clean

tp5: $(OBJS)
	gcc  $(OBJS) -ldl -lSDL2 -lsplash -o $(EXE)

liba: $(OBJS)
	ar crs libsplash.a actions.o player.o world.o render.o bomb.o

affiche:
	@echo TOTO

libso: affiche all 
	gcc -shared -o libsplash.so actions.o main.o player.o world.o

clean: 
	$(DEL) -f core
	rm -f *.a
	rm -f *.so
	rm -f $(OBJS)
	rm -f $(EXE)


