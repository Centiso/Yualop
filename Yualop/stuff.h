/**
 * \file stuff.h
 * \brief Programme des prototypes et structures de stuff.c
 * \details Création et mise à jour des statistiques objets de l'équipement
 * \author Cécile SAIVET
 * \version 1.2
 * \date 17 Mars 2021
 */


#ifndef _STUFF_H_
#define _STUFF_H_

typedef struct {
	char nom[20];

	int lvl;
	int durabilite;
	int att;
	int def;
	int categ;

} t_objet ; //Objets

typedef struct {
	t_objet *head;
	t_objet *chest;
	t_objet *gloves;
	t_objet *legs;
	t_objet *feet;
	t_objet *main_hand;
	t_objet *off_hand;
} t_stuff ; //Emplacement où les objets seront affectés

t_objet *crea_obj (int level, int cat);
void maj_lvl_obj(t_objet *obj);

#endif
