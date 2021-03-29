#include "commun.h"

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
                        vie = 1;
                        break;
            
                        default:
                            vie = 0.5;
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

void affiche_drop(SDL_Renderer *renderer, SDL_Rect *cadavre, SDL_Texture *stuff[], t_objet *drop)
{   
    SDL_Rect posCadavre;
    posCadavre.x = cadavre->x;
    posCadavre.y = cadavre->y;
    posCadavre.w = posCadavre.h = TAILLE_BLOCK;

    SDL_RenderCopy(renderer, stuff[drop->categ], NULL, &posCadavre);
}