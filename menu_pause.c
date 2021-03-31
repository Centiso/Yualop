#include "commun.h"

void in_game_options(SDL_Window *window, SDL_Renderer *renderer)
{
	//
}

/**-------------------------Initialisation de fond-------------------------**/
//ICI
    // Initialize support for loading PNG and JPEG images
//Refaire ça fonctionne pas
void image_stuff(SDL_Renderer *renderer){
    SDL_Texture * image_texture = initialize_texture_from_file("images/earth_chan.png", renderer);

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, 20, 10);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 1200;
    texture_destination.y = HEIGHT/2;
    texture_destination.w = 20;
    texture_destination.h = 10;
}
///Affichage du menu pause lorsque le joueur est en jeu.
SDL_bool menu_pause(SDL_Window *window, SDL_Renderer *renderer, t_pers *player)
{
    SDL_Rect rect_reprendre, rect_options, rect_quitter;
    SDL_Rect /*rect_nom,*/ rect_level, rect_pdv, rect_att, rect_def; //ICI

	const int taille_police = 72;
  const int t_police_stats = 38; //ICI taille police stats may be réduire encore

  rect_level.w =rect_pdv.w= rect_att.w= rect_def.w= WIDTH-WIDTH*0.70; //ICI largeur du blanc
  rect_level.h=rect_att.h= rect_pdv.h= rect_def.h=  taille_police+10; //ICI hauteur du blanc
  rect_level.x=rect_pdv.x=rect_att.x= rect_def.x=  (WIDTH-rect_level.w)/28; //ICI place en x du rect
//  rect_nom.y=HEIGHT-7*(HEIGHT/8); //ICI place en y des rect
  rect_level.y=HEIGHT-7*(HEIGHT/8); //ICI
  rect_pdv.y= HEIGHT-5*(HEIGHT/8); //ICI
  rect_att.y=HEIGHT-3*(HEIGHT/8); //ICI
  rect_def.y=HEIGHT-1*(HEIGHT/8); //ICI

	rect_reprendre.w = rect_options.w = rect_quitter.w = WIDTH-WIDTH*0.65;
	rect_reprendre.h = rect_options.h = rect_quitter.h = taille_police + 10;
	rect_reprendre.x = rect_options.x = rect_quitter.x = (WIDTH-rect_reprendre.w)/2;
	rect_reprendre.y = HEIGHT-3*(HEIGHT/4);
	rect_options.y = HEIGHT-2*(HEIGHT/4);
	rect_quitter.y = HEIGHT-1*(HEIGHT/4);

    TTF_Font *police = TTF_OpenFont(NOM_FONT, taille_police);
    TTF_Font *police_stats = TTF_OpenFont(NOM_FONT, t_police_stats); //ICI

    if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

    SDL_SetRenderDrawColor(renderer, A_R, A_G, A_B, 200);

	SDL_RenderFillRect(renderer, &rect_reprendre);
	SDL_RenderFillRect(renderer, &rect_options);
	SDL_RenderFillRect(renderer, &rect_quitter);

  SDL_SetRenderDrawColor(renderer, 0, 128, 128, 200); //Change couleur rect stats
//    SDL_RenderFillRect(renderer, &rect_nom);//ICI
    SDL_RenderFillRect(renderer, &rect_level);//ICI
    SDL_RenderFillRect(renderer, &rect_pdv);//ICI
    SDL_RenderFillRect(renderer, &rect_att);//ICI
    SDL_RenderFillRect(renderer, &rect_def);//ICI

	SDL_SetRenderDrawColor(renderer, P_R, P_R, P_R, 200);

	SDL_RenderDrawRect(renderer, &rect_reprendre);
	SDL_RenderDrawRect(renderer, &rect_options);
	SDL_RenderDrawRect(renderer, &rect_quitter);

//  SDL_RenderDrawRect(renderer, &rect_nom);//ICI
  SDL_RenderDrawRect(renderer, &rect_level);//ICI
  SDL_RenderDrawRect(renderer, &rect_pdv);//ICI
  SDL_RenderDrawRect(renderer, &rect_att);//ICI
  SDL_RenderDrawRect(renderer, &rect_def);//ICI



	creerTexte(renderer, police, "REPRENDRE", WIDTH/2 - 7 * 21, rect_reprendre.y - 5);
	creerTexte(renderer, police, "OPTIONS", WIDTH/2 - 7 * 17, rect_options.y - 5);
	creerTexte(renderer, police, "QUITTER", WIDTH/2 - 7 * 18, rect_quitter.y - 5);

//  creerTexte(renderer, police_stats, "NOM", WIDTH/28, rect_nom.y-3); //ICI se place à gauche
  creerTexte(renderer, police_stats, "Niveau", WIDTH/28, rect_level.y-3); //ICI
  creerTexte(renderer, police_stats, "Points de Vie", WIDTH/28, rect_pdv.y-3); //ICI
  creerTexte(renderer, police_stats, "Attaque", WIDTH/28, rect_att.y-3); //ICI
  creerTexte(renderer, police_stats, "Defense", WIDTH/28, rect_def.y-3); //ICI

  char level[5];
  char pdv[5];
  char att[5];
  char def[5];

  sprintf(level,"%d", player->lvl);
  sprintf(pdv,"%d", player->pdv);
  sprintf(att,"%d", player->att);
  sprintf(def,"%d", player->def);


  creerTexte(renderer, police_stats, level, WIDTH/28*6, rect_level.y+10); //ICI
  creerTexte(renderer, police_stats, pdv, WIDTH/28*6, rect_pdv.y+10); //ICI
  creerTexte(renderer, police_stats, att, WIDTH/28*6, rect_att.y+10); //ICI
  creerTexte(renderer, police_stats, def, WIDTH/28*6, rect_def.y+10); //ICI

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

	free(police);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

    if (reprendre_asked)
		return SDL_TRUE;
	else if (quitter_asked)
		return SDL_FALSE;
}
