/**
 * \file fonctions.c
 * \brief Contient des fonctions utilisées pour le jeu
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date 2021
 */

#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

///Fonction pour créer une texture à partir d'une image
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

///Fonction de gestion d'erreur qui affiche l'erreur SDL rencontrée et libère la mémoire allouée avant de quitter le programme.
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

///Fonction testant si un clique a lieu dans le rectangle passé en paramètres.
SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect);

///Fonction affichant un texte "str" sur le renderer aux coordonées passées en paramètres.
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y, SDL_Color color);

///Delay utilisé pour la limite de fps
void delay(unsigned int frameLimit);

#endif
