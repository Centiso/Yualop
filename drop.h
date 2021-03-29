#ifndef _DROP_H_
#define _DROP_H_

#include "stuff.h"

t_objet *drop (int levelMonstre);
void affiche_drop(SDL_Renderer *renderer, SDL_Rect *cadavre, SDL_Texture *stuff[], t_objet *drop);

#endif