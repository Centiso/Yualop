#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_
#include "commun.h"

extern void mouvement(int Carte[][26], SDL_Rect *pos, int Direction, SDL_Renderer *render);
int jouer(SDL_Renderer *render , SDL_Window *window);

#endif