CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS =  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
EXEC = peggy

$(EXEC) : $(OBJETS)
	$(CC) -o $@ $^ $(LDFLAGS)

depends.txt : $(SOURCES)
	$(CC) -M  $(SOURCES) > depends.txt

include depends.txt

.PHONY : clean apocalypse

clean :
	rm *.o depends.txt

apocalypse:clean
	rm $(EXEC)
