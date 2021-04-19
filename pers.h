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

<<<<<<< HEAD
 typedef struct {
  char nom[20] ;
  int att;
  int def;
  int pdv;
  int lvl; //numéro étage donjon
 } t_pers ;

 typedef struct{
   t_pers joueurs;
   t_pers mechants;
 } t_categories;



t_pers *crea_pers (int faction, int level);
void maj_lvl(int faction, t_pers *player);


// SDL_Rect rect_nom, rect_att, rect_def, rect_pdv, rect_level; //ICI
=======
t_pers *crea_pers (int faction, int level);
void maj_lvl(int level, t_pers *player);

#endif
>>>>>>> Florian
