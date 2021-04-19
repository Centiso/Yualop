/**
 * \file stuffv2.h
 * \brief Programme des prototype et structure de stuffv2.c
 * \details oublie pas les prototypes
 * \author Cécile SAIVET
 * \version 1.0
 * \date 17 Mars 2021
 */


 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<time.h>

#include "pers.h"

 enum categ {CASQUE, PLASTRON, GANTS, JAMBIERES, BOTTES, OFF_HAND, MAIN_HAND};

 typedef struct {
 // char nom[20] ;
 // char desc[100];
  int lvl;
  int durabilite;
  int att;
  int def;
  int categ; // Ce que c'est

 } t_objet ; //Objets

 typedef struct {
  t_objet head ;
  t_objet arm_D;
  t_objet arm_G;
  t_objet legs;
  t_objet feet;
  t_objet chest; //pecs

 } t_stuff ; // L'emplacement où objt sera affecté

 t_objet *crea_obj (int level, int cat);

 void maj_lvl_obj(int level, t_objet *obj);
