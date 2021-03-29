/**
 * \file pers.c
 * \brief Contient les fonctions liées aux personnages (joueur comme bot)
 * \author SAIVET Cécile, SANNA Florian
 * \version 1.0
 * \date 2021
 */

#include "commun.h"

/**
 * \fn t_pers *crea_pers(int faction, int level)
 * \brief Fonction de création d'un personnage.
 * \return Le personnage créé en mémoire dynamique.
 */
t_pers *crea_pers(int faction, int level)
{
	t_pers *player;

	player = malloc(sizeof(t_pers)*1);

	if(faction == GENTIL)
	{
		player->pdv = 100;
		player->def = 50;
		player->atq = 100;
		player->lvl = level;
	}

	else if (faction == MECHANT)
	{
		player->pdv = 100;
		player->def = 25;
		player->atq = 55;
	}

	player->faction = faction;

	return (player);
}

/**
 * \fn void destruction_pers(t_pers *player)
 * \brief Fonction de destruction de personnage.
 */
void destruction_pers(t_pers *player)
{
	free(player);
	player = NULL;
}

/**
 * \fn void maj_lvl(int level, t_pers *player)
 * \brief Fonction de mise à jour de niveau d'un t_pers passé en paramètre.
 */
void maj_lvl(int level, t_pers *player)
{
	int i;

	if (player->faction == GENTIL){
		for (i = 0; i<level; i++)
		{
			player->pdv *= 1.1;
			player->def  *= 1.1;
			player->atq *= 1.1;
		}
	}
  
	else if (player->faction == MECHANT){
		for (i = 0; i<level; i++)
		{
			player->pdv *= 1.1;
			player->def  *= 1.1;
			player->atq *= 1.1;
		}
	}
}