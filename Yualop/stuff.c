/**
 * \file stuff.c
 * \brief Programme de statistiques équipements
 * \details Création et mise à jour des statistiques objets de l'équipement
 * \author Cécile SAIVET
 * \version 1.1
 * \date 17 Mars 2021
 */

// Consigne : Faire struct t_equipement avec tête, bras, jambes etc... le rattacher à t_pers
#include "commun.h"
//Protos + struct irons dans pers.h
//Le prog ira dans persp.c

/**
 * \fn t_objet *crea_obj (int level, int cat)
 * \brief Création d'objet
 * \details  Crée un objet en fonction de sa catégorie et du niveau du pallier atteint
 * \param level Niveau de l'objet
 * \param cat Catégorie de l'objet
 * \return Retourne l'objet créé
 */
 t_objet *crea_obj (int level, int cat)
{
    t_objet *item;
    item = malloc(sizeof(t_objet)*1);

    switch (cat)
    {
        case HEAD :
            item->durabilite=5;
            item->att=0;
            item->def=3;
            break;

        case CHEST:
            item->durabilite=5;
            item->att=2;
            item->def=0;
            break;

        case GLOVES:
            item->durabilite=1000;
            item->att=0;
            item->def=15;
            break;

        case LEGS:
            item->durabilite=500;
            item->att=0;
            item->def=25;
            break;

        case FEET:
            item->durabilite=100000;
            item->att=0;
            item->def=5;
            break;

        case MAIN_HAND:
            item->durabilite=1000;
            item->att=4;
            item->def=5;
            break;

        case OFF_HAND:
            item->durabilite=1000;
            item->att=4;
            item->def=5;
            break;

        case HEART:
            item->durabilite=1;
            item->att=0;
            item->def=0;
            break;

        case HALF_HEART:
            item->durabilite=1;
            item->att=0;
            item->def=0;
            break;
    }
    item->categ = cat;
    item->lvl = level;

    return (item);
}

/**
 * \fn void maj_lvl_obj(int level, t_objet *obj)
 * \brief Mise à jour de l'objet
 * \details  Les statistique de l'objet sont changé en fonction de sa catégorie et du niveau du pallier atteint
 * \param level Niveau actuel de l'objet
 * \param *obj Objet à modifier
 * \return Ne retourne rien il s'agit d'un void
 */
 void maj_lvl_obj(t_objet *obj){

    for (int i = 0; i < obj->lvl; i++)
    {
        obj->durabilite *= rand()%6;
        obj->att *= rand()%6;
    }
}
