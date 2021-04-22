/**
 * \file commun.h
 * \brief Fichier regroupant les constantes et librairies utilisées dans les différents fichiers.
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date Mars 2021
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
#include "pile.h"
#include "menu_settings.h"

///Déclaration des constantes

unsigned int WIDTH;  ///Largeur de la fenêtre principale
unsigned int HEIGHT; ///Hauteur de la fenêtre principale

#define TAILLE_BLOCK (HEIGHT / MAP_MAX_Y)

#define NOM_FONT "polices/LLHP.ttf"

///Définitions pour le jeu.c

typedef enum s_direction{HAUT, BAS, GAUCHE, DROITE} t_direction;

typedef enum s_obstacle{VIDE, MUR = -1, JOUEUR} t_obstacle;

#define RANGE_JOUEUR 3
#define RANGE_BOT 1

///Définitions pers.c

typedef enum s_faction{GENTIL, MECHANT} t_faction;

#define DEFAULT_LEVEL 1

///Définition stuff.c / drop.c

typedef enum s_categorie{HEAD, CHEST, GLOVES, LEGS, FEET, MAIN_HAND, OFF_HAND, HEART, HALF_HEART} t_categorie;

///Définition map.c
#define TILE_SIZE 16
#define MAP_MAX_Y 26
#define MAP_MAX_X 26
#define FAUX 0
#define VRAI 1
#define COULOIR 0
#define CHEMIN -2
#define N 10
#define M 10

///Code RGB de la police d'écriture

#define P_R 25
#define P_G 25
#define P_B 25

///Code RGB des rectangles d'affichage

#define A_R 125
#define A_G 125
#define A_B 125

#endif