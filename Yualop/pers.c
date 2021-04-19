/**
 * \file pers.c
 * \brief Programme de création de personnage + mise à jour statistiques
 * \details Création et mise à jour des statistiques personnages
 * \author Cécile SAIVET, Florian SANNA
 * \version 1.4
 * \date 08 Mars 2021
 */

#include "commun.h"

/**
* \fn t_pers *crea_pers (int faction, int level)
* \brief Création d'un personnage
* \details Fonction qui crée le personnage joueur et les ennemis
* \param faction Donne l'appartenance du personnage (gentil ou méchant)
* \param level Donne le pallier ou le personnage est rendu
* \return Retourne le personnage créée
*/
t_pers *crea_pers(int faction, int level)
{
	t_pers *player;

	player = malloc(sizeof(t_pers)*1);

	switch(faction)
	{
		case GENTIL:
			player->pdv = 100;
			player->def = 50;
			player->att = 100;
			player->lvl = level;
			break;

		case MECHANT:
			player->pdv = 100;
			player->def = 25;
			player->att = 55;
			break;
	}

	player->faction = faction;
	player->alive = 1;

	return (player);
}

/**
* \fn void maj_lvl(int faction, t_pers *player)
* \brief Augmentation des statistiques
* \details Fonction qui met à jour les statistiques personnages par pallier
* \param faction Prend l'appartemence du personnage
* \param *player Prend le personnage à modifier
* \return Ne retourne rien il s'agit d'un void
*/
void maj_lvl(int level, t_pers *player)
{
	int i;

	if (player->faction == GENTIL){
		for (i = 0; i<level; i++)
		{
			player->pdv *= 1.1;
			player->def *= 1.1;
			player->att *= 1.1;
		}
	}

	else if (player->faction == MECHANT){
		for (i = 0; i<level; i++)
		{
			player->pdv *= 1.1;
			player->def *= 1.1;
			player->att *= 1.1;
		}
	}
}
