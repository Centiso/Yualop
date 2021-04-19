/**
 * \file drop.c
 * \brief Contient les fonctions liées aux drops
 * \author TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date Avril 2021
 */

#include "commun.h"

/**
 * \fn t_objet *drop (int levelMonstre)
 * \brief Décide si un objet est drop ou non, et le créé dans le cas où il l'est.
 * \return Retourne un t_objet si le monstre tué en drop un.
 */
t_objet *drop (int levelMonstre)
{
	int dropChance, aleaDrop , obj_cat, vieDrop, vie;

	obj_cat = rand()%7;
	dropChance = rand()%10;
	vieDrop = rand()%20;
	aleaDrop = rand()%10;
	t_objet *item = NULL; 

	switch(dropChance)
	{
		case 1 :
			switch (aleaDrop)
			{
				case 1:
					switch (vieDrop)
					{
						case 1:
							item = crea_obj(levelMonstre, HEART);
							break;
			
						default:
							item = crea_obj(levelMonstre, HALF_HEART);
							break;
					}
					break;
			
				default:
					item = crea_obj(levelMonstre, obj_cat);
					maj_lvl_obj(item);
					break;
			}
			break;
			
		default :
			break;
	}
	return item;
}

/**
 * \fn void affiche_drop(SDL_Renderer *renderer, SDL_Rect *cadavre, SDL_Texture *stuff[], t_objet *drop)
 * \brief Affiche un objet à l'emplacement du mob tué.
 */
void affiche_drop(SDL_Renderer *renderer, SDL_Rect *cadavre, SDL_Texture *stuff[], t_objet *drop)
{   
	SDL_Rect posCadavre;
	posCadavre.x  = cadavre->x + TAILLE_BLOCK;
	posCadavre.y  = cadavre->y + TAILLE_BLOCK;
	posCadavre.w = posCadavre.h = TAILLE_BLOCK;

	SDL_RenderCopy(renderer, stuff[drop->categ], NULL, &posCadavre);
}

/**
 * \fn int recupere_drop(SDL_Rect *joueur, SDL_Rect *cadavre, t_objet *drop, t_stuff *playerStuff, t_pers *playerStats)
 * \brief Ajoute l'objet récupéré dans l'inventaire du joueur si le joueur a les mêmes coordonnées que l'objet.
 * \return 1 dans le cas où l'objet est récupéré, 0 sinon.
 */
int recupere_drop(SDL_Rect *joueur, SDL_Rect *cadavre, t_objet *drop, t_stuff *playerStuff, t_pers *playerStats)
{
	if (joueur->x + TAILLE_BLOCK == cadavre->x + TAILLE_BLOCK && joueur->y + TAILLE_BLOCK == cadavre->y + TAILLE_BLOCK)
	{
		switch (drop->categ)
		{
			case HEAD:
				playerStuff->head = drop;
				break;
			
			case CHEST:
				playerStuff->chest = drop;
				break;
			
			case GLOVES:
				playerStuff->gloves = drop;
				break;

			case LEGS:
				playerStuff->legs = drop;
				break;

			case FEET:
				playerStuff->feet = drop;
				break;

			case MAIN_HAND:
				playerStuff->main_hand = drop;
				break;

			case OFF_HAND:
				playerStuff->off_hand = drop;
				break;
			
			case HEART:
				playerStats->pdv += 10;
				break;

			case HALF_HEART:
				playerStats->pdv += 5;
				break;
		}
		return 1;
	}
	else
		return 0;
}
