/**
 * \file main_menu.c
 * \brief Contient le menu principal de Yualop
 * \author SAIVET Cécile, TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date 2021
 */

#include "commun.h"

/**
 * \fn SDL_bool menu(SDL_Window *window, SDL_Renderer *renderer)
 * \brief Fonction affichant un menu permettant a l'utilisateur de naviguer dans le programme.
 * \return SDL_TRUE si le joueur reste sur le jeu, SDL_FALSE sinon.
 */
SDL_bool menu(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Rect rect_new_game, rect_load_game, rect_settings, rect_exit;
	const int taille_police = 72;

	rect_new_game.w = rect_load_game.w = rect_settings.w = rect_exit.w = WIDTH-WIDTH*0.65;
	rect_new_game.h = rect_load_game.h = rect_settings.h = rect_exit.h = taille_police + 10;
	rect_new_game.x = rect_load_game.x = rect_settings.x = rect_exit.x = (WIDTH-rect_new_game.w)/2;
	rect_new_game.y =  HEIGHT-4*(HEIGHT/5);
	rect_load_game.y = HEIGHT-3*(HEIGHT/5);
	rect_settings.y =  HEIGHT-2*(HEIGHT/5);
    rect_exit.y =      HEIGHT-1*(HEIGHT/5);

	TTF_Font *police = TTF_OpenFont(NOM_FONT, taille_police);

	SDL_Color NOIR = {P_R, P_G, P_B};

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

	SDL_SetRenderDrawColor(renderer, A_R, A_G, A_B, 255);

	SDL_RenderFillRect(renderer, &rect_new_game);
	SDL_RenderFillRect(renderer, &rect_load_game);
	SDL_RenderFillRect(renderer, &rect_settings);
    SDL_RenderFillRect(renderer, &rect_exit);

	SDL_SetRenderDrawColor(renderer, P_R, P_G, P_B, 255);

	SDL_RenderDrawRect(renderer, &rect_new_game);
	SDL_RenderDrawRect(renderer, &rect_load_game);
	SDL_RenderDrawRect(renderer, &rect_settings);
    SDL_RenderDrawRect(renderer, &rect_exit);

	int widthTemp;
	
	TTF_SizeText(police, "NEW GAME", &widthTemp, NULL);
	creerTexte(renderer, police, "NEW GAME",  WIDTH/2 - widthTemp/2, rect_new_game.y - 5, NOIR);
	
	TTF_SizeText(police, "LOAD GAME", &widthTemp, NULL);
	creerTexte(renderer, police, "LOAD GAME", WIDTH/2 - widthTemp/2, rect_load_game.y - 5, NOIR);
	
	TTF_SizeText(police, "SETTINGS", &widthTemp, NULL);
	creerTexte(renderer, police, "SETTINGS",  WIDTH/2 - widthTemp/2, rect_settings.y - 5, NOIR);
    
	TTF_SizeText(police, "EXIT", &widthTemp, NULL);
	creerTexte(renderer, police, "EXIT",      WIDTH/2 - widthTemp/2, rect_exit.y - 5, NOIR);

 	SDL_RenderPresent(renderer);

	SDL_Event event;
	SDL_bool menu_launched = SDL_TRUE;

	SDL_bool new_game_asked = SDL_FALSE;
	SDL_bool load_game_asked = SDL_FALSE;
	SDL_bool setting_asked = SDL_FALSE;
    SDL_bool exit_asked = SDL_FALSE;

	while (menu_launched){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: 
					menu_launched = SDL_FALSE;
					exit_asked = SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_new_game)){
							new_game_asked = SDL_TRUE; 
							menu_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_load_game)){
							load_game_asked = SDL_TRUE;
							menu_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_settings)){
							setting_asked = SDL_TRUE;
							menu_launched = SDL_FALSE;
						}
                        else if (clickSurCase(event, rect_exit)){
                            exit_asked = SDL_TRUE;
                            menu_launched = SDL_FALSE;
                        }
					}
					break;

				/*case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_F11: 
							//SDL_SetWindowSize(window, 1400, 800);
							printf("F11");
							break;
					}
					break;*/
			}
	}

	free(police);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

	if (new_game_asked)
	{
		jouer(renderer, window);
		return SDL_TRUE;
	}
	else if (load_game_asked)
	{
		printf("Load Game.");
	}
	else if (setting_asked)
	{
		printf("Settings.");
	}
    else if (exit_asked)
	{
        printf("Bisous.");
		return SDL_FALSE;
	}
}
