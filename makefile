detected_OS = 
CC = gcc

SDL_DIR = ../..
SDLLIB_DIR = ${SDL_DIR}/lib
SDLINC_DIR = ${SDL_DIR}/include
SDLBIN_DIR = ${SDL_DIR}/bin

LIB = -L ${SDLLIB_DIR} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDE = -I ${SDLINC_DIR}
LDFLAGS = $(LIB) $(INCLUDE)

LLIB = -ldl `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_ttf
LLDFLAGS = $(LLIB) 

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS), Windows)
Yualop : $(OBJ)
	$(CC) -o $(SDLBIN_DIR)/$@ $^ $(LDFLAGS)

%.o : %.c 
	$(CC) -o $@ -c $< $(LDFLAGS)

clean : 
	del *.o

else
Yualop : $(OBJ)
	$(CC) -o $(SDLBIN_DIR)/$@ $^ $(LLDFLAGS)

%.o : %.c 
	$(CC) -o $@ -c $< $(LLDFLAGS) 

clean :
	rm -f *.o core
endif