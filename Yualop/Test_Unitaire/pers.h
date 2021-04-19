/**
 * \file pers.h
 * \brief Programme de je sais pas trop j'essaie de créer un personnage
 * \details Version avec pointeurs
 * \author Cécile SAIVET
 * \version 1.2
 * \date 08 Mars 2021
 */

#ifndef _PERS_H_
#define _PERS_H_

typedef struct s_pers{
	int att;
	int def;
	int pdv;
	int faction;
	int lvl;
	int alive;
} t_pers;

t_pers *crea_pers (int faction, int level);
void destruction_pers(t_pers *player);
void maj_lvl(int level, t_pers *player);

#endif
