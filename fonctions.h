#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

///Fonction de gestion d'erreur qui affiche l'erreur SDL rencontrée et libère la mémoire allouée avant de quitter le programme.
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

///Fonction testant si un clique a lieu dans le rectangle passé en paramètres.
SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect);

///Fonction affichant un texte "str" sur le renderer aux coordonées passées en paramètres.
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y);

///Delay utilisé pour la limite de fps
void delay(unsigned int frameLimit);

#endif