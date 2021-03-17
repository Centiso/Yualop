#include "commun.h"

int main(int argc, char** argv)
{
/**-------------------------Déclaration des variables principales-------------------------**/

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_bool program_launched = SDL_TRUE;

	const unsigned int FPS = 60;
	const unsigned int frameDelay = 1000 / FPS;

	unsigned long long frameStart;
	int frameTime;

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

	menu(window, renderer);

	while(program_launched)
	{
		frameStart = SDL_GetTicks();
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			printf("%i, %i\n", event.button.x, event.button.y);
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							printf("Le jeu est désormais en pause.\n");
							program_launched = menu_pause(window, renderer);
							break;
					}
					break;

				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
			}
		}

		frameTime = SDL_GetTicks() - frameStart; //FPS Limiter

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

/**-------------------------Libération de la mémoire allouée-------------------------**/

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

/**-------------------------Fin du programme-------------------------**/

	return EXIT_SUCCESS;
}