#include "commun.h"

void in_game_options(SDL_Window *window, SDL_Renderer *renderer)
{
	//
}

///Affichage du menu pause lorsque le joueur est en jeu.
SDL_bool menu_pause(SDL_Window *window, SDL_Renderer *renderer, t_pers *player)
{
	SDL_Rect rect_reprendre, rect_options, rect_quitter;
	SDL_Rect rect_level, rect_pdv, rect_atq, rect_def;

	SDL_Color NOIR = {P_R, P_G, P_B};

	const int taille_police = 72;
	const int taille_stats = 38;

	rect_level.w = rect_pdv.w = rect_atq.w = rect_def.w = WIDTH-WIDTH*0.70;
	rect_level.h = rect_atq.h = rect_pdv.h = rect_def.h = taille_police+10;
	rect_level.x = rect_pdv.x = rect_atq.x = rect_def.x = (WIDTH-rect_level.w)/28;
	
	rect_level.y = HEIGHT - 7*(HEIGHT/8);
	rect_pdv.y	 = HEIGHT - 5*(HEIGHT/8);
	rect_atq.y	 = HEIGHT - 3*(HEIGHT/8);
	rect_def.y	 = HEIGHT - 1*(HEIGHT/8);

	rect_reprendre.w = rect_options.w = rect_quitter.w = WIDTH-WIDTH*0.65;
	rect_reprendre.h = rect_options.h = rect_quitter.h = taille_police + 10;
	rect_reprendre.x = rect_options.x = rect_quitter.x = (WIDTH-rect_reprendre.w)/2;
	rect_reprendre.y = HEIGHT-3*(HEIGHT/4);
	rect_options.y = HEIGHT-2*(HEIGHT/4);
	rect_quitter.y = HEIGHT-1*(HEIGHT/4);

	TTF_Font *police = TTF_OpenFont(NOM_FONT, taille_police);
	TTF_Font *police_stats = TTF_OpenFont(NOM_FONT, taille_stats);

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

	if (!police_stats)
		SDL_ExitWithError("Erreur du chargement de la police stats", window, renderer, NULL);

    SDL_SetRenderDrawColor(renderer, A_R, A_G, A_B, 200);

	SDL_RenderFillRect(renderer, &rect_reprendre);
	SDL_RenderFillRect(renderer, &rect_options);
	SDL_RenderFillRect(renderer, &rect_quitter);

	SDL_SetRenderDrawColor(renderer, 0, 128, 128, 200);
	SDL_RenderFillRect(renderer, &rect_level);
	SDL_RenderFillRect(renderer, &rect_pdv);
	SDL_RenderFillRect(renderer, &rect_atq);
	SDL_RenderFillRect(renderer, &rect_def);

	SDL_SetRenderDrawColor(renderer, P_R, P_R, P_R, 200);

	SDL_RenderDrawRect(renderer, &rect_reprendre);
	SDL_RenderDrawRect(renderer, &rect_options);
	SDL_RenderDrawRect(renderer, &rect_quitter);

	SDL_RenderDrawRect(renderer, &rect_level);
	SDL_RenderDrawRect(renderer, &rect_pdv);
	SDL_RenderDrawRect(renderer, &rect_atq);
	SDL_RenderDrawRect(renderer, &rect_def);

	int widthTemp, heightTemp;
	
	TTF_SizeText(police, "REPRENDRE", &widthTemp, NULL);
	creerTexte(renderer, police, "REPRENDRE", WIDTH/2 - widthTemp/2, rect_reprendre.y - 5, NOIR);
	
	TTF_SizeText(police, "OPTIONS", &widthTemp, NULL);
	creerTexte(renderer, police, "OPTIONS", WIDTH/2 - widthTemp/2, rect_options.y - 5, NOIR);
	
	TTF_SizeText(police, "QUITTER", &widthTemp, NULL);
	creerTexte(renderer, police, "QUITTER", WIDTH/2 - widthTemp/2, rect_quitter.y - 5, NOIR);

	creerTexte(renderer, police_stats, "Niveau", rect_level.x + 5, rect_level.y, NOIR);
	creerTexte(renderer, police_stats, "Points de Vie", rect_pdv.x + 5, rect_pdv.y, NOIR);
	creerTexte(renderer, police_stats, "Attaque", rect_atq.x + 5, rect_atq.y, NOIR);
	creerTexte(renderer, police_stats, "Defense", rect_def.x + 5, rect_def.y, NOIR);

	char level[5];
	char pdv[5];
	char atq[5];
	char def[5];

	sprintf(level, "%d", player->lvl);
	sprintf(pdv,   "%d", player->pdv);
	sprintf(atq,   "%d", player->atq);
	sprintf(def,   "%d", player->def);

	TTF_SizeText(police, level, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, level, rect_level.x + rect_level.w - widthTemp, rect_level.y + rect_level.h - heightTemp, NOIR);
	
	TTF_SizeText(police, pdv, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, pdv, rect_pdv.x + rect_pdv.w - widthTemp, rect_pdv.y + rect_pdv.h - heightTemp, NOIR);
	
	TTF_SizeText(police, atq, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, atq, rect_atq.x + rect_atq.w - widthTemp, rect_atq.y + rect_atq.h - heightTemp, NOIR);
	
	TTF_SizeText(police, def, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, def, rect_def.x + rect_def.w - widthTemp, rect_def.y + rect_def.h - heightTemp, NOIR);

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
						case SDLK_ESCAPE:
							pause_launched = SDL_FALSE;
							reprendre_asked = SDL_TRUE;
							break;
					}
			}
	}

	free(police_stats);
	free(police);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

    if (reprendre_asked)
		return SDL_TRUE;
	else if (quitter_asked)
		return SDL_FALSE;
}