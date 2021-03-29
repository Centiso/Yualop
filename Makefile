
detected_OS = 
CC = gcc

SDL_DIR = ../..
SDLLIB_DIR = ${SDL_DIR}/lib
SDLINC_DIR = ${SDL_DIR}/include
SDLBIN_DIR = ${SDL_DIR}/bin

LIB = -L ${SDLLIB_DIR} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
LLIB = -L ${SDLLIB_DIR} -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDE = -I ${SDLINC_DIR}

LDFLAGS = $(LIB) $(INCLUDE)
LLDFLAGS = $(LLIB) $(INCLUDE)

SDL = -ldl `sdl2-config --libs`
LDFLAGSU = $(SDL) -lSDL2 -lSDL2_image -lSDL2_ttf

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

#$@ nom de la cible;
#$< nom de la première;
#$^ liste des dépendances;

#all : $(EXEC)

#Version Simple et efficace

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
else
Yualop : $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGSU) 

%.o : %.c 
	$(CC) -Wall $< -c `sdl2-config --cflags` -o $@  

endif



#VERSION POUR FAIRE PLAISIR MAIS ELLE ME CASSE BIEN LES COUILLES CAR ELLE EST TROP LONGUE A FAIRE

#Yualop : menu_pause.o jeu.o fonctions.o main_menu.o main.o
#	$(CC) -o Yualop menu_pause.o jeu.o fonctions.o main_menu.o main.o $(LDFLAGS)

#main.o : main.c 
#	$(CC) -o main.o -c main.c $(LDFLAGS)

#menu_pause.o : menu_pause.c menu_pause.h
#	$(CC) -o menu_pause.o -c menu_pause.c $(LDFLAGS)

#jeu.o : jeu.c jeu.h
#	$(CC) -o jeu.o -c jeu.c $(LDFLAGS)

#fonctions.o : fonctions.c fonctions.h
#	$(CC) -o fonctions.o -c fonctions.c $(LDFLAGS)

#main_menu.o : main_menu.c main_menu.h
#	$(CC) -o main_menu.o -c main_menu.c $(LDFLAGS)


clean :
	rm -f *.o
