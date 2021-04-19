/**
 * \file menu_pause.c
 * \brief Programme SDL affichage menu pause
 * \details Contient les statistiques et l'inventaire, base venu du main_menu.c
 * \author Cécile SAIVET
 * \version 1.3
 * \date 12 Avril 2021
 */

#include "commun.h"

void in_game_options(SDL_Window *window, SDL_Renderer *renderer)
{
	//
}

/**
 * \fn SDL_bool menu_pause(SDL_Window *window, SDL_Renderer *renderer, t_pers *player, t_stuff playerStuff)
 * \brief Affichage du menu pause lorsque le joueur est en jeu.
 * \param window Prend la fênetre de jeu 
 * \param renderer Récupère le calque en cours
 * \param player Récupère les statistiques du joueur
 * \param playerStuff Recueil les informations de l'inventaire du joueur en temps réel
 * \return Affiche le menu pause sur un calque au dessus du calque de la fenêtre de jeu actuel
 */

SDL_bool menu_pause(SDL_Window *window, SDL_Renderer *renderer, t_pers *player, t_stuff playerStuff)
{
	SDL_Rect rect_reprendre, rect_options, rect_quitter;
	SDL_Rect rect_level, rect_pdv, rect_att, rect_def;

	SDL_Color NOIR = {P_R, P_G, P_B};

	const int taille_police = 72;
	const int taille_stats = 38;

	rect_reprendre.w = rect_options.w = rect_quitter.w = WIDTH-WIDTH*0.65;
	rect_reprendre.h = rect_options.h = rect_quitter.h = taille_police + 10;
	rect_reprendre.x = rect_options.x = rect_quitter.x = (WIDTH-rect_reprendre.w)/2;
	rect_reprendre.y = HEIGHT-3*(HEIGHT/4);
	rect_options.y = HEIGHT-2*(HEIGHT/4);
	rect_quitter.y = HEIGHT-1*(HEIGHT/4);

	rect_level.w = rect_pdv.w = rect_att.w = rect_def.w = WIDTH-WIDTH*0.70;
	rect_level.h = rect_att.h = rect_pdv.h = rect_def.h = rect_reprendre.h;
	rect_level.x = rect_pdv.x = rect_att.x = rect_def.x = (WIDTH-rect_level.w)/28;
	rect_level.y = HEIGHT - 5*(HEIGHT/8);
	rect_pdv.y	 = HEIGHT - 4*(HEIGHT/8);
	rect_att.y	 = HEIGHT - 3*(HEIGHT/8);
	rect_def.y	 = HEIGHT - 2*(HEIGHT/8);

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
	SDL_RenderFillRect(renderer, &rect_att);
	SDL_RenderFillRect(renderer, &rect_def);

	SDL_SetRenderDrawColor(renderer, P_R, P_R, P_R, 200);

	SDL_RenderDrawRect(renderer, &rect_reprendre);
	SDL_RenderDrawRect(renderer, &rect_options);
	SDL_RenderDrawRect(renderer, &rect_quitter);

	SDL_RenderDrawRect(renderer, &rect_level);
	SDL_RenderDrawRect(renderer, &rect_pdv);
	SDL_RenderDrawRect(renderer, &rect_att);
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
	creerTexte(renderer, police_stats, "Attaque", rect_att.x + 5, rect_att.y, NOIR);
	creerTexte(renderer, police_stats, "Defense", rect_def.x + 5, rect_def.y, NOIR);

	char level[5];
	char pdv[5];
	char att[5];
	char def[5];

	sprintf(level, "%d", player->lvl);
	sprintf(pdv,   "%d", player->pdv);
	sprintf(att,   "%d", player->att);
	sprintf(def,   "%d", player->def);

	TTF_SizeText(police_stats, level, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, level, rect_level.x + rect_level.w - widthTemp - 3, rect_level.y + rect_level.h - heightTemp, NOIR);

	TTF_SizeText(police_stats, pdv, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, pdv, rect_pdv.x + rect_pdv.w - widthTemp - 3, rect_pdv.y + rect_pdv.h - heightTemp, NOIR);

	TTF_SizeText(police_stats, att, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, att, rect_att.x + rect_att.w - widthTemp - 3, rect_att.y + rect_att.h - heightTemp, NOIR);

	TTF_SizeText(police_stats, def, &widthTemp, &heightTemp);
	creerTexte(renderer, police_stats, def, rect_def.x + rect_def.w - widthTemp - 3, rect_def.y + rect_def.h - heightTemp, NOIR);




//_______   PARTIE DE TEST SPECIFIQUE :  _________//
        		//création de ton rectangle
		SDL_Rect rect_pers_stuff;

		rect_pers_stuff.h = HEIGHT/2; //Hauteur image
		rect_pers_stuff.w = WIDTH/4; //Largeur image
		rect_pers_stuff.x = (WIDTH-rect_pers_stuff.w)-75; //Position du personnage en x (0 = gauche)
		rect_pers_stuff.y = HEIGHT/2 - (rect_pers_stuff.h / 2); //Position en y (0 = en haut)
/*
		//chargement de la texture (il te faut une varibale SDL_Texture *, une variable SDL_Surface * et SDL_Renderer *, initialisées à NULL)
		SDL_Texture * texture_stuff;
		texture_stuff = SDL_CreateTextureFromSurface(renderer, pers_stuff);

		//ensuite on nettoie la surface (vu qu'on a enregistré son contenue dans la texture on en a plus besoin pour le moment)
		SDL_FreeSurface(pers_stuff);
*/
//Initialisation nouvelle texture et Initialisation de la texture via l'image
		SDL_Texture * texture_stuff = initialize_texture_from_file("images/perso.png", renderer);

		//ensuite on charge le rectangle (sinon l'image est l'image de base et ne peux pas décider où elle se trouvera sur le rendu, donc besoin de la variable renderer, texture et rect)
		SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_pers_stuff);

    //___________ITEMS STUFF____________________//
    SDL_Rect rect_item_stuff;

//________________Test pop stuff____________//
    if ( playerStuff.head != NULL ) {

     //____________________HEAD_____________________//
     	rect_item_stuff.h = HEIGHT/5; //Hauteur image
     	rect_item_stuff.w = WIDTH/7; //Largeur image
     	rect_item_stuff.x = rect_pers_stuff.x+60; //Position en x 0 = gauche
     	rect_item_stuff.y = rect_pers_stuff.y-70 ; //Position en y 0 = en haut

     	texture_stuff = initialize_texture_from_file("images/stuff/head.png", renderer);
     	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

    }

//__________________Changer position entre chaque image__________________//
if ( playerStuff.head != NULL ) {
  //____________________HEAD_____________________//
  	rect_item_stuff.h = HEIGHT/5; //Hauteur image
  	rect_item_stuff.w = WIDTH/7; //Largeur image
  	rect_item_stuff.x = rect_pers_stuff.x+60; //Position en x 0 = gauche
  	rect_item_stuff.y = rect_pers_stuff.y-70 ; //Position en y 0 = en haut

  	texture_stuff = initialize_texture_from_file("images/stuff/head.png", renderer);
  	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);


}

if ( playerStuff.legs != NULL ) {
  //____________________LEGS_____________________//
   rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
   rect_item_stuff.w = WIDTH/7; //Largeur image
   rect_item_stuff.x = rect_pers_stuff.x+80; //Position en x 0 = gauche
   rect_item_stuff.y = rect_pers_stuff.y+150 ; //Position en y 0 = en haut

   texture_stuff = initialize_texture_from_file("images/stuff/legs.png", renderer);
   SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

}

if ( playerStuff.feet != NULL ) {

  //____________________FEET_____________________//
  	rect_item_stuff.h = HEIGHT/5; //Hauteur image
  	rect_item_stuff.w = WIDTH/7; //Largeur image
  	rect_item_stuff.x = rect_pers_stuff.x+87; //Position en x 0 = gauche
  	rect_item_stuff.y = rect_pers_stuff.y+222 ; //Position en y 0 = en haut

  	texture_stuff = initialize_texture_from_file("images/stuff/feet.png", renderer);
  	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);
}


  if ( playerStuff.chest != NULL ) {
    //____________________CHEST_____________________//
    rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
    rect_item_stuff.w = WIDTH/7; //Largeur image
    rect_item_stuff.x = rect_pers_stuff.x+70; //Position en x 0 = gauche
    rect_item_stuff.y = rect_pers_stuff.y +80; //Position en y 0 = en haut

    /*
      SDL_FreeSurface(chest);  // Déjà présent dans la fonction d'initialisation
    */
       texture_stuff = initialize_texture_from_file("images/stuff/chest.png", renderer);
       SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

  }
  if ( playerStuff.gloves != NULL ) {
//____________________GLOVES_____________________//
	rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
	rect_item_stuff.w = WIDTH/7; //Largeur image
	rect_item_stuff.x = rect_pers_stuff.x-60; //Position en x 0 = gauche
	rect_item_stuff.y = rect_pers_stuff.y+130 ; //Position en y 0 = en haut

	texture_stuff = initialize_texture_from_file("images/stuff/gloves.png", renderer);
	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

}
  if ( playerStuff.main_hand != NULL ) {
//____________________MAIN_HAND_____________________//
	rect_item_stuff.h = HEIGHT/4; //Hauteur image
	rect_item_stuff.w = WIDTH/7; //Largeur image
	rect_item_stuff.x = rect_pers_stuff.x+255; //Position en x 0 = gauche
	rect_item_stuff.y = rect_pers_stuff.y+50 ; //Position en y 0 = en haut

	texture_stuff = initialize_texture_from_file("images/stuff/main_hand.png", renderer);
	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);
}
  if ( playerStuff.off_hand != NULL ) {
//____________________OFF_HAND_____________________//
	rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
	rect_item_stuff.w = WIDTH/7; //Largeur image
	rect_item_stuff.x = rect_pers_stuff.x-150; //Position en x 0 = gauche
	rect_item_stuff.y = rect_pers_stuff.y+100; //Position en y 0 = en haut

	texture_stuff = initialize_texture_from_file("images/stuff/off_hand.png", renderer);
	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

}




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
