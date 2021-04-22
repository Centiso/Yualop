/**
 * \file fonctions.c
 * \brief Contient des fonctions utilisées pour le jeu
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date Mars 2021
 */

#include "commun.h"

/**
 * \fn void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
 * \brief Fonction utilisée en cas d'erreur SDL.
 * \return Affiche l'erreur dans la console et ferme le programme en libérant la mémoire.
 */
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);

	if(strcmp(message, "IMG_Init"))
		IMG_Quit();
	if(TTF_WasInit())
		TTF_Quit();
	if(SDL_WasInit(SDL_INIT_VIDEO))
    	SDL_Quit();

    exit(EXIT_FAILURE);
}

/**
 * \fn SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect)
 * \brief Regarde si l'utilisateur a cliqué sur une case passée en paramètre.
 * \return SDL_TRUE si le clique est sur le rectangle, SDL_FALSE sinon.
 */
SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect)
{
	return (	click.button.y > caseRect.y
			&& 	click.button.y < caseRect.y + caseRect.h
			&& 	click.button.x > caseRect.x
			&&	click.button.x < caseRect.x + caseRect.w);
}

/**
 * \fn void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y)
 * \brief Création d'un texte passé en paramètre à l'emplacement passé en paramètre.
 */
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y, SDL_Color color)
{
	SDL_Surface *texte = NULL;
	SDL_Rect txtDestRect;

	texte = TTF_RenderUTF8_Blended(police, str, color);
	if (!texte){
		fprintf (stderr, "Erreur a la creation du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
	}
	SDL_Texture * texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	if (!texte_tex){
		fprintf(stderr, "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
	}
	txtDestRect.x = x;
  	txtDestRect.y = y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);

	SDL_FreeSurface(texte);
	SDL_DestroyTexture(texte_tex);
}

/**
 * \fn void delay(unsigned int frameLimit)
 * \brief Fonction utilisée pour la limite d'image par seconde (en ms).
 */
void delay(unsigned int frameLimit)
{
	// Gestion des 60 fps (images/stories/seconde)
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}

	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}

	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

/**
 * \fn SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
 * \brief Créé une texture à partir d'un fichier.
 * \return Texture du fichier passé en paramètre.
 */
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
{
	SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return image_texture;
}