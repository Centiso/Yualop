/**
 * \file commun.h
 * \brief Fichier regroupant les constantes et librairies utilisées dans les différents fichiers.
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 **/

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
#include "jeu.h"


///Déclaration des constantes

#define WIDTH 1260
#define HEIGHT 720

#define NOM_FONT "polices/LLHP.ttf"

#define TAILLE_BLOCK 34

///Définitions pour le jeu.c

typedef enum s_direction{HAUT, BAS, GAUCHE, DROITE} t_direction;

typedef enum s_obstacle{VIDE, MUR, JOUEUR} t_obstacle;

#define RANGE_JOUEUR 2
#define RANGE_BOT 1

///Définitions pers.c

typedef enum s_faction{GENTIL, MECHANT} t_faction;

typedef enum s_niveau{DEFAULT_LEVEL = 1} t_niveau;

///Code RGB de la police d'écriture

#define P_R 25
#define P_G 25
#define P_B 25

///Code RGB des rectangles d'affichage

#define A_R 125
#define A_G 125
#define A_B 125

#endif
