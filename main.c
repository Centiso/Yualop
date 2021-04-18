/**
 * \file main.c
 * \brief Fichier principal du jeu Yualop
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date 2021
 */

#include "commun.h"


/**
 * \fn int main(int argc, char** argv)
 * \brief Fonction principale du jeu.
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main(int argc, char** argv)
{
/**-------------------------Déclaration des variables principales-------------------------**/

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *icon = NULL;

	SDL_DisplayMode current;

	SDL_bool program_launched = SDL_TRUE;

/**-------------------------Initialisation SDL et librairies-------------------------**/

  	if (SDL_Init(SDL_INIT_VIDEO) != 0)
  		SDL_ExitWithError("SDL_Init", NULL, NULL, NULL);

	if(!TTF_WasInit() && TTF_Init() == -1)
		SDL_ExitWithError("TTF_Init", NULL, NULL, NULL);
	
	///Initialize support for loading PNG and JPEG images
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		SDL_ExitWithError("IMG_Init", NULL, NULL, NULL);

	if (SDL_GetCurrentDisplayMode(0, &current) != 0)
		SDL_ExitWithError("Current display error", NULL, NULL, NULL);

	WIDTH = current.w;
	HEIGHT = current.h;
	
	/* if (WIDTH != current.w){
		WIDTH = 1400;
		HEIGHT = 800;
	}
	*/
	///Création de la fenêtre
	window = SDL_CreateWindow("Yualop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenêtre", window, NULL, NULL);

	///Création du rendu
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer", window, renderer, NULL);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

/**-------------------------Initialisation de fond-------------------------**/

    SDL_Texture * image_texture = initialize_texture_from_file("images/Fox.jpg", renderer);
    int image_width, image_height;

	///Création de l'icône
	icon = IMG_Load("images/Yualop.png");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

    ///Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    ///Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = WIDTH;
    texture_destination.h = HEIGHT;

/**-------------------------Programme principal-------------------------**/
	while(program_launched)
	{
		//Clear screen
		SDL_RenderClear(renderer);

		//Draw
		SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

		//Show what was drawn
		SDL_RenderPresent(renderer);

		program_launched = menu(window, renderer);
	}

/**-------------------------Libération de la mémoire allouée-------------------------**/

	SDL_DestroyTexture(image_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

/**-------------------------Fin du programme-------------------------**/

	return (EXIT_SUCCESS);
}