CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS =  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
SOURCES = $(wildcard *.c)
SOURCES_GAME = $(filter-out lvlEditor.c,$(SOURCES))
OBJETS_GAME = $(SOURCES_GAME:.c=.o)
SOURCES_EDITOR = $(filter-out main.c,$(SOURCES))
OBJETS_EDITOR = $(SOURCES_EDITOR:.c=.o)
EXEC = peggy
EXEC_EDITOR = editor

$(EXEC) : $(OBJETS_GAME)
	$(CC) -o $@ $^ $(LDFLAGS)
$(EXEC_EDITOR) : $(OBJETS_EDITOR)
	$(CC) -o $@ $^ $(LDFLAGS)

depends.txt : $(SOURCES)
	$(CC) -M  $(SOURCES) > depends.txt

include depends.txt

.PHONY : clean apocalypse

clean :
	rm *.o $(EXEC) $(EXEC_EDITOR) depends.txt
