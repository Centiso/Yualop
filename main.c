#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
/**Fonction de gestion d'erreur qui affiche l'erreur SDL rencontrée et libère la mémoire allouée avant de quitter le programme**/
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();

    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
/**-------------------------Déclaration des variables principales-------------------------**/

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_bool program_launched = SDL_TRUE;

/**-------------------------Initialisation SDL et librairies-------------------------**/

  	if (SDL_Init(SDL_INIT_VIDEO) != 0)
  		SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	if(!TTF_WasInit() && TTF_Init() == -1)
		SDL_ExitWithError("TTF_Init", NULL, NULL, NULL);

	///Création de la fenêtre
	window = SDL_CreateWindow("Yualop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenêtre\n", window, NULL, NULL);

	///Création du rendu
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window, renderer, NULL);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
/**-------------------------Programme principal-------------------------**/

	while(program_launched)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			printf("%i, %i\n", event.button.x, event.button.y);
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_b:
							printf("Vous avez appuyé sur B\n");
							break;
					}
					break;

				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
			}
		}
	}

/**-------------------------Libération de la mémoire allouée-------------------------**/

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

/**-------------------------Fin du programme-------------------------**/

	return EXIT_SUCCESS;
}