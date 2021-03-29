#include "commun.h"

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
{
	SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return image_texture;
}


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

/**-------------------------Initialisation de fond-------------------------**/

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * image_texture = initialize_texture_from_file("images/Fox.jpg", renderer);
    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = image_width;
    texture_destination.h = image_height;

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

	return EXIT_SUCCESS;
}