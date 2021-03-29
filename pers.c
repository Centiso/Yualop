/**
 * \file pers.c
 * \brief Programme de création de personnage pluS le level up des stats
 * \details Version avec pointeurs regroupement de statiques.c et pers.c
 * \author Cécile SAIVET
 * \version 1.3
 * \date 08 Mars 2021
 */

#include "commun.h"

t_pers *crea_pers(int faction, int level)
{
	t_pers *player;

	player = malloc(sizeof(t_pers)*1);

	if(faction == GENTIL)
	{
		player->pdv = 100;
		player->def = 50;
		player->att = 5;
		player->lvl = level;
	}

	else if (faction == MECHANT){
		player->pdv = 100;
		player->def = 25;
		player->att = 3;
	}

	player->faction = faction;

	return (player);
}

void destruction_pers(t_pers *player)
{
	free(player);
	player = NULL;
}

void maj_lvl(int level, t_pers *player)
{
	int i;

	if (player->faction == GENTIL){
		for (i = 0; i<level; i++)
		{
			player->pdv *= 1.1;
			player->def  *= 1.1;
			player->att *= 1.1;
		}
	}
  
	else if (player->faction == MECHANT){
		for (i = 0; i<level; i++)
		{
			player->pdv *= 1.1;
			player->def  *= 1.1;
			player->att *= 1.1;
		}
	}
}
