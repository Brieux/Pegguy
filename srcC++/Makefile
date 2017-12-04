CC = g++
CFLAGS = -Wall -g
LDFLAGS =  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
SOURCES = $(wildcard *.cpp)
SOURCES_GAME = $(SOURCES)
OBJETS_GAME = $(SOURCES_GAME:.cpp=.o)
EXEC = peggy

$(EXEC) : $(OBJETS_GAME)
	$(CC) -o $@ $^ $(LDFLAGS)

depends.txt : $(SOURCES)
	$(CC) -M  $(SOURCES) > depends.txt

include depends.txt

.PHONY : clean apocalypse

clean :
	rm -f *.o $(EXEC) depends.txt
