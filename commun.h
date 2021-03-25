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

#include "menu_pause.h"
#include "fonctions.h"
#include "main_menu.h"

///Déclaration des constantes

#define WIDTH 1280
#define HEIGHT 960

#define NOM_FONT "polices/LLHP.ttf"

#define CASE_SIZE (WIDTH/HEIGHT)*12

///Code RGB de la police d'écriture

#define P_R 25
#define P_G 25
#define P_B 25

///Code RGB des rectangles d'affichage

#define A_R 125
#define A_G 125
#define A_B 125

#endif