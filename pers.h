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
 } t_pers ;

 typedef struct{
   t_pers joueurs;
   t_pers mechants;
 } t_categories;

 typedef struct {
   int niveau;
   int pdv;
   int def;
   int att;
 } t_levels;
