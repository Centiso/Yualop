#include "commun.h"

//Retourne un objet si le monstre tué en drop un
t_objet *drop (int levelMonstre)
{
	
	int dropChance, aleaDrop , obj_cat, vieDrop, vie;

	obj_cat = rand()%7;
	dropChance = rand()%1000;
	vieDrop = rand()%20;
	aleaDrop = rand()%10;
	t_objet *item = NULL; 

	switch(1) //dropChance
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

//Affiche un objet à l'emplacement du mob tué
void affiche_drop(SDL_Renderer *renderer, SDL_Rect *cadavre, SDL_Texture *stuff[], t_objet *drop)
{   
	SDL_Rect posCadavre;
	posCadavre.x = cadavre->x;
	posCadavre.y = cadavre->y;
	posCadavre.w = posCadavre.h = TAILLE_BLOCK;

	SDL_RenderCopy(renderer, stuff[drop->categ], NULL, &posCadavre);
}

//
int recupere_drop(SDL_Rect *joueur, SDL_Rect *cadavre, t_objet *drop, t_stuff *playerStuff, t_pers *playerStats)
{
	if (joueur->x == cadavre->x && joueur->y == cadavre->y)
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
