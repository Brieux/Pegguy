CC = g++
CFLAGS = -std=c99 -g -Wall
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.c=.o)
EXEC = test_cpp
CPPFLAGS = -I ../include2
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

.PHONY:all clean_tmp clean

all: EXEC clean_tmp

include depend.txt

EXEC: $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $(EXEC)

depend.txt: $(SRC)
	$(CC) $(CPPFLAGS) -MM $^ > $@

clean_tmp:
	rm -rf *.o depend.txt

clean: clean_tmp
	rm -rf $(EXEC)
