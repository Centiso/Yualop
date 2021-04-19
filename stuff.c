/**
 * \file stuff.c
 * \brief Programme de stats stuff
 * \details Version avec pointeurs
 * \author SAIVET Cécile
 * \version 1.1
 * \date Mars 2021
 */

#include "commun.h"

/**
 * \fn t_objet *crea_obj (int level, int cat)
 * \brief Créé et alloue dynamiquement un objet avec un niveau et une catégorie passés en paramètre.
 * \return Retourne l'objet créé.
 */
t_objet *crea_obj (int level, int cat)
{
    t_objet *item;
    item = malloc(sizeof(t_objet)*1);

    switch (cat)
    {
        case HEAD : 
            item->durabilite=5;
            item->atq=0;
            item->def=3;
            break;

        case CHEST: 
            item->durabilite=5;
            item->atq=2;
            item->def=0;
            break;

        case GLOVES:    
            item->durabilite=1000;
            item->atq=0;
            item->def=15;
            break;

        case LEGS:  
            item->durabilite=500;
            item->atq=0;
            item->def=25;
            break;

        case FEET:    
            item->durabilite=100000;
            item->atq=0;
            item->def=5;
            break;

        case MAIN_HAND:    
            item->durabilite=1000;
            item->atq=4;
            item->def=5;
            break;
        
        case OFF_HAND:
            item->durabilite=1000;
            item->atq=4;
            item->def=5;
            break;
        
        case HEART:
            item->durabilite=1;
            item->atq=0;
            item->def=0;
            break;

        case HALF_HEART:
            item->durabilite=1;
            item->atq=0;
            item->def=0;
            break;
    }
    item->categ = cat;
    item->lvl = level;

    return (item);
}


/**
 * \fn void maj_lvl_obj(t_objet *obj)
 * \brief Met à jour les stats de l'objet en fonction de son niveau.
 */
void maj_lvl_obj(t_objet *obj){

    for (int i = 0; i < obj->lvl; i++)
    {
        obj->durabilite *= rand()%6;
        obj->atq *= rand()%6;
    }
}

