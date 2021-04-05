#ifndef _PERS_H_
#define _PERS_H_

typedef struct s_pers{
	int atq;
	int def;
	int pdv;
	int faction;
	int lvl;
	int alive;
} t_pers;

t_pers *crea_pers (int faction, int level);
void maj_lvl(int level, t_pers *player);

#endif