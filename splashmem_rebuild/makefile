CC = gcc
CFLAGS = -Wall -g2 -I./include
SRCDIR = src
INCDIR = include

SRCFILES = $(wildcard $(SRCDIR)/*.c)
HDRFILES = $(wildcard $(INCDIR)/*.h)
OBJFILES = $(patsubst $(SRCDIR)/%.c, %.o, $(SRCFILES))

TARGET = splash

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@ -lSDL2

%.o: $(SRCDIR)/%.c $(HDRFILES)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run clean

run: $(TARGET)
	chmod +x $(TARGET)
	./$(TARGET) pl/p1.so pl/p2.so pl/p3.so pl/p4.so

clean:
	rm -f $(OBJFILES) $(TARGET)
