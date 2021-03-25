/**
 * \file statiques.c
 * \brief Programme de je sais pas trop j'essaie de créer un personnage
 * \details Version avec pointeurs
 * \author Cécile SAIVET
 * \version 1.2
 * \date 08 Mars 2021
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

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
