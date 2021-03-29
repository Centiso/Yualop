#ifndef _PERS_H_
#define _PERS_H_

typedef struct s_pers{
	int atq;
	int def;
	int pdv;
	int faction;
	int lvl;
} t_pers;

t_pers *crea_pers (int faction, int level);
void destruction_pers(t_pers *player);
void maj_lvl(int level, t_pers *player);

#endif