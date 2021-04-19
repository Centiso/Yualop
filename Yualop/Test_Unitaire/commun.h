/**
 * \file commun.h
 * \brief Fichier regroupant les constantes et librairies utilisées dans les différents fichiers.
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date 2021
 */

#ifndef _COMMUN_H_
#define _COMMUN_H_

///Déclaration des librairies

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "pers.h"
#include "menu_pause.h"
#include "fonctions.h"
#include "main_menu.h"
#include "stuff.h"
#include "drop.h"
#include "map.h"
#include "jeu.h"

///Déclaration des constantes

#define WIDTH 1270 //Largeur de la fenêtre principale
#define HEIGHT 720 //Hauteur de la fenêtre principale

#define TAILLE_BLOCK (HEIGHT / MAP_MAX_Y)

#define NOM_FONT "polices/LLHP.ttf"

///Définitions pour le jeu.c

typedef enum s_direction{HAUT, BAS, GAUCHE, DROITE} t_direction;

typedef enum s_obstacle{VIDE, MUR, JOUEUR} t_obstacle;

#define RANGE_JOUEUR 3
#define RANGE_BOT 1

///Définitions pers.c

typedef enum s_faction{GENTIL, MECHANT} t_faction;

#define DEFAULT_LEVEL 1

///Définition stuff.c / drop.c
/*
typedef enum s_categorie{HEAD, CHEST, GLOVES, LEGS, FEET, MAIN_HAND, OFF_HAND, HEART, HALF_HEART} t_categorie;*/

///Code RGB de la police d'écriture

#define P_R 25
#define P_G 25
#define P_B 25

///Code RGB des rectangles d'affichage

#define A_R 125
#define A_G 125
#define A_B 125

#endif
