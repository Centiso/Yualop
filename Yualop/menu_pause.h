/**
 * \file menu_pause.h
 * \brief Programme des prototypes et structures de menu_pause.c
 * \details Contient les statistiques et l'inventaire, base venu du main_menu.c
 * \author Cécile SAIVET
 * \version 1.3
 * \date 12 Avril 2021
 */


#ifndef _MENU_PAUSE_H_
#define _MENU_PAUSE_H_

void in_game_options(SDL_Window *window, SDL_Renderer *renderer);

SDL_bool menu_pause(SDL_Window *window, SDL_Renderer *renderer, t_pers *player, t_stuff playerStuff);

#endif
