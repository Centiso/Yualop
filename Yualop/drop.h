/**
 * \file drop.h
 * \brief Contient les structures du drop
 * \author TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date 2021
 */


#ifndef _DROP_H_
#define _DROP_H_

#include "stuff.h"

t_objet *drop (int levelMonstre);
void affiche_drop(SDL_Renderer *renderer, SDL_Rect *cadavre, SDL_Texture *stuff[], t_objet *drop);
int recupere_drop(SDL_Rect *joueur, SDL_Rect *cadavre, t_objet *drop, t_stuff *playerStuff, t_pers *playerStats);

#endif
