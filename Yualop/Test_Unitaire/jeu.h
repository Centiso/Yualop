#ifndef _JEU_H_
#define _JEU_H_

#define MAP_MAX_Y 26
#define MAP_MAX_X 26

void mouvement(int carte[][MAP_MAX_X], SDL_Rect *pos, int Direction, SDL_Renderer *render);
void attaque(int carte[][MAP_MAX_X], SDL_Rect *pos , int direction, SDL_Renderer *render, int rangeAttaque);
int jouer(SDL_Renderer *render , SDL_Window *window);

#endif