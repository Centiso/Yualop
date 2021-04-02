#ifndef _JEU_H_
#define _JEU_H_

void mouvement(int carte[][MAP_MAX_X], SDL_Rect *pos, int Direction, SDL_Renderer *render);
int hitMarker(int direction, SDL_Rect *srcPos, SDL_Rect *destPos, int rangeAttaque);
void attaque(int carte[][MAP_MAX_X], SDL_Rect *srcPos, SDL_Rect *destPos, int direction, SDL_Renderer *render, int rangeAttaque, t_pers *srcAtq, t_pers *destAtq);
int botActions(int carte[][MAP_MAX_X], SDL_Rect *botTueur, SDL_Rect *joueur, SDL_Renderer *render, t_pers *srcAtq, t_pers *destAtq);
void jouer(SDL_Renderer *render , SDL_Window *window);
void changementMap(SDL_Rect *joueur, SDL_Rect *bot, int direction);

#endif