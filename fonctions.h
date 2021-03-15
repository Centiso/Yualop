#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect);

void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y);

#endif