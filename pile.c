#include "commun.h"

/**
 * \file jeu.c
 * \brief Contient les fonction pour la gestion de la pile
 * \author TACHET Nicolas
 * \version 1.0
 * \date Avril 2021
 */

/**
 * \fn Pile *initialiser
 * \brief initialise la pile
 */
Pile *initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}

/**
 * \fn void empiler(Pile *pile, int nvNombre)
 * \brief empile la valeur dans la pile
 */
void empiler(Pile *pile, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

/**
 * \fn int depiler(Pile *pile)
 * \brief dépile la valeur dans la pile
 */
int depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDepile = 0;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL)
    {
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return nombreDepile;
}
