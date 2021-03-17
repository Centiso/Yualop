SDL = -ldl `sdl2-config --libs`
LDFLAGS = $(SDL) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2_mixer


prog: main.o actions.o draw.o init.o input.o SDL2_rotozoom.o
    gcc main.o actions.o draw.o init.o input.o SDL2_rotozoom.o $(LDFLAGS) -o prog


main.o: main.c main.h struct.h defs.h
    gcc -Wall main.c -c `sdl2-config --cflags`

actions.o: actions.c actions.h struct.h defs.h
    gcc -Wall actions.c -c `sdl2-config --cflags`

draw.o: draw.c draw.h struct.h defs.h
    gcc -Wall draw.c -c `sdl2-config --cflags`

init.o: init.c init.h struct.h defs.h
    gcc -Wall init.c -c `sdl2-config --cflags`

input.o: input.c input.h struct.h defs.h
    gcc -Wall input.c -c `sdl2-config --cflags`

SDL2_rotozoom.o: SDL2_rotozoom.c SDL2_rotozoom.h struct.h defs.h
    gcc -Wall SDL2_rotozoom.c -c `sdl2-config --cflags`
