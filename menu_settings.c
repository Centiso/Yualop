#include "commun.h"

/**
 * \file main_menu.c
 * \brief Contient le menu d'affichage de Yualop
 * \author TACHET Nicolas
 * \version 1.0
 * \date Avril 2021
 */

/**
 * \fn SDL_bool menu(SDL_Window *window, SDL_Renderer *renderer)
 * \brief Fonction affichant un menu d'option pour pouvoir jouer en plein écran ou en fenêtré
 */
SDL_bool menu_settings(SDL_Window *window, SDL_Renderer *renderer){

    SDL_Rect rect_fullscreen, rect_windowed, rect_back;
    const int taille_police = 72;

    rect_fullscreen.w = rect_windowed.w = rect_back.w = WIDTH-WIDTH*0.65;
	rect_fullscreen.h = rect_windowed.h = rect_back.h = taille_police + 10;
	rect_fullscreen.x = rect_windowed.x = rect_back.w = (WIDTH-rect_fullscreen.w)/2;

    rect_fullscreen.y = HEIGHT-3*(HEIGHT/5);
	rect_windowed.y =  HEIGHT-2*(HEIGHT/5);
    rect_back.y = HEIGHT-1*(HEIGHT/5);

	TTF_Font *police = TTF_OpenFont(NOM_FONT, taille_police);

	SDL_Color NOIR = {P_R, P_G, P_B};

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

    SDL_SetRenderDrawColor(renderer, A_R, A_G, A_B, 255);

    SDL_RenderFillRect(renderer, &rect_fullscreen);
	SDL_RenderFillRect(renderer, &rect_windowed);
    SDL_RenderFillRect(renderer, &rect_back);

    SDL_SetRenderDrawColor(renderer, P_R, P_G, P_B, 255);

    SDL_RenderFillRect(renderer, &rect_fullscreen);
	SDL_RenderFillRect(renderer, &rect_windowed);
    SDL_RenderFillRect(renderer, &rect_back);

    int widthTemp;

    TTF_SizeText(police, "FULL SCREEN", &widthTemp, NULL);
	creerTexte(renderer, police, "FULL SCREEN",  WIDTH/2 - widthTemp/2, rect_fullscreen.y - 5, NOIR);

    TTF_SizeText(police, "WINDOWED", &widthTemp, NULL);
	creerTexte(renderer, police, "WINDOWED",  WIDTH/2 - widthTemp/2, rect_windowed.y - 5, NOIR);

    TTF_SizeText(police, "BACK", &widthTemp, NULL);
	creerTexte(renderer, police, "BACK",  WIDTH/2 - widthTemp/2, rect_back.y - 5, NOIR);

    SDL_Event event;
	SDL_bool menu_launched = SDL_TRUE;

    SDL_bool fullscreen_asked = SDL_FALSE;
	SDL_bool windowed_asked = SDL_FALSE;
	SDL_bool back_asked = SDL_FALSE;

    while (menu_launched){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: 
					menu_launched = SDL_FALSE;
					back_asked = SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_fullscreen)){
							fullscreen_asked = SDL_TRUE; 
							menu_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_windowed)){
							windowed_asked = SDL_TRUE;
							menu_launched = SDL_FALSE;
						}
                        else if (clickSurCase(event, rect_back)){
                            back_asked = SDL_TRUE;
                            menu_launched = SDL_FALSE;
                        }
					}
					break;
	        }
    }
    free(police);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    if (fullscreen_asked)
	{
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else if (windowed_asked)
	{
		SDL_SetWindowSize(window, 1280, 720);
		SDL_RenderClear(renderer);
	}
    else if (back_asked)
	{
		return;
	}
}