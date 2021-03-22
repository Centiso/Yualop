#include "commun.h"

void in_game_options(SDL_Window *window, SDL_Renderer *renderer)
{
	//
}

///Affichage du menu pause lorsque le joueur est en jeu.
SDL_bool menu_pause(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect rect_reprendre, rect_options, rect_quitter;
	const int taille_police = 72;

	rect_reprendre.w = rect_options.w = rect_quitter.w = WIDTH-WIDTH*0.65;
	rect_reprendre.h = rect_options.h = rect_quitter.h = taille_police + 10;
	rect_reprendre.x = rect_options.x = rect_quitter.x = (WIDTH-rect_reprendre.w)/2;
	rect_reprendre.y = HEIGHT-3*(HEIGHT/4);
	rect_options.y = HEIGHT-2*(HEIGHT/4);
	rect_quitter.y = HEIGHT-1*(HEIGHT/4);

    TTF_Font *police = TTF_OpenFont(NOM_FONT, taille_police);

    if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

    SDL_SetRenderDrawColor(renderer, R_R, R_G, R_B, 255);

	SDL_RenderFillRect(renderer, &rect_reprendre);
	SDL_RenderFillRect(renderer, &rect_options);
	SDL_RenderFillRect(renderer, &rect_quitter);

	SDL_SetRenderDrawColor(renderer, P_R, P_R, P_R, 255);

	SDL_RenderDrawRect(renderer, &rect_reprendre);
	SDL_RenderDrawRect(renderer, &rect_options);
	SDL_RenderDrawRect(renderer, &rect_quitter);

	creerTexte(renderer, police, "REPRENDRE", WIDTH/2 - 7 * 21, rect_reprendre.y - 5);
	creerTexte(renderer, police, "OPTIONS", WIDTH/2 - 7 * 17, rect_options.y - 5);
	creerTexte(renderer, police, "QUITTER", WIDTH/2 - 7 * 18, rect_quitter.y - 5);

 	SDL_RenderPresent(renderer);

    SDL_Event event;

	SDL_bool pause_launched = SDL_TRUE;

	SDL_bool reprendre_asked = SDL_FALSE;
	SDL_bool quitter_asked = SDL_FALSE;

	while (pause_launched){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: pause_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_reprendre)){
							reprendre_asked = SDL_TRUE; 
							pause_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_options)){
							printf("Options");
							in_game_options(window, renderer);
						}
						else if (clickSurCase(event, rect_quitter)){
							quitter_asked = SDL_TRUE;
							pause_launched = SDL_FALSE;
						}
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: pause_launched = SDL_FALSE;break;
					}
			}
	}

	free(police);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

    if (reprendre_asked)
		return SDL_TRUE;
	else if (quitter_asked)
		return SDL_FALSE;
}