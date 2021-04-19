/**
 * \file test_insert_stats.c
 * \brief Programme SDL Menu + stats
 * \details Réarrangement du menu_pause pour y ajouter les stats
 * \author SAIVET Cécile
 * \version 1.0
 * \date Mars 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "pers.h"

#define WIDTH 1260
#define HEIGHT 720

#define NOM_FONT "polices/LLHP.ttf"



///Fonction de gestion d'erreur qui affiche l'erreur SDL rencontrée et libère la mémoire allouée avant de quitter le programme.
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
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

///Fonction testant si un clique a lieu dans le rectangle passé en paramètres.
SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect){
	return (	click.button.y > caseRect.y
			&& 	click.button.y < caseRect.y + caseRect.h
			&& 	click.button.x > caseRect.x
			&&	click.button.x < caseRect.x + caseRect.w);
}

/*
  ///Fonction affichant un entier "int" sur le renderer aux coordonées passées en paramètres.
  void creerInt(SDL_Renderer *renderer, TTF_Font *police, int enti, int x, int y){
  	SDL_Surface entier;
  	SDL_Rect intDestRect;
  	SDL_Color NOIR = {0, 0, 0};

entier = TTF_RenderUTF8_Blended(police,entier,NOIR);
if(!entier){
  fprintf(stderr, "Erreur a la creation de l'entier : %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
}
SDL_Texture * texte_tex = SDL_CreateTextureFromSurface(renderer, entier);
if (!texte_tex){
  fprintf(stderr, "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
  exit(EXIT_FAILURE);
}
SDL_FreeSurface(entier);
  intDestRect.x = x;
  intDestRect.y = y;
SDL_QueryTexture(texte_tex, NULL, NULL, &(intDestRect.w), &(intDestRect.h));
SDL_RenderCopy(renderer, texte_tex, NULL, &intDestRect);
} */


///Fonction affichant un texte "str" sur le renderer aux coordonées passées en paramètres.
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y){
	SDL_Surface *texte = NULL;
	SDL_Rect txtDestRect;
	SDL_Color NOIR = {0, 0, 0};

	texte = TTF_RenderUTF8_Blended(police, str, NOIR);
	if (!texte){
		fprintf (stderr, "Erreur a la creation du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
	}
	SDL_Texture * texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	if (!texte_tex){
		fprintf(stderr, "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(texte);
	txtDestRect.x = x;
  	txtDestRect.y = y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
}

///Affichage du menu pause lorsque le joueur est en jeu.
int main(int argc, char *argv[])
{
  t_pers *player;
  player=crea_pers(0,1);
      //strcpy(player->nom, "Blue");


    SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

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
//ICI
      // Initialize support for loading PNG and JPEG images
      IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

      SDL_Texture * image_texture = initialize_texture_from_file("earth_chan.jpeg", renderer);
      int image_width, image_height;

      // Get texture width/height
      SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

      // Define where on the "screen" we want to draw the texture
      SDL_Rect texture_destination;

      texture_destination.x = 1200;
      texture_destination.y = HEIGHT/2;
      texture_destination.w = image_width;
      texture_destination.h = image_height;

    /**-------------------------menu_pause.c-------------------------**/

    SDL_Rect rect_reprendre, rect_options, rect_quitter;
    SDL_Rect rect_nom, rect_level, rect_pdv, rect_att, rect_def; //ICI

	const int taille_police = 72;
  const int t_police_stats = 38; //ICI taille police stats may be réduire encore

  rect_nom.w=rect_level.w =rect_pdv.w= rect_att.w= rect_def.w= WIDTH-WIDTH*0.70; //ICI largeur du blanc
  rect_nom.h=rect_level.h=rect_att.h= rect_pdv.h= rect_def.h=  taille_police+10; //ICI hauteur du blanc
  rect_nom.x=rect_level.x=rect_pdv.x=rect_att.x= rect_def.x=  (WIDTH-rect_nom.w)/28; //ICI place en x du rect
  rect_nom.y=HEIGHT-7*(HEIGHT/8); //ICI place en y des rect
  rect_level.y=HEIGHT-6*(HEIGHT/8); //ICI
  rect_pdv.y= HEIGHT-5*(HEIGHT/8); //ICI
  rect_att.y=HEIGHT-4*(HEIGHT/8); //ICI
  rect_def.y=HEIGHT-3*(HEIGHT/8); //ICI



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

    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);

	SDL_RenderFillRect(renderer, &rect_reprendre);
	SDL_RenderFillRect(renderer, &rect_options);
	SDL_RenderFillRect(renderer, &rect_quitter);

SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255); //Change couleur rect stats
  SDL_RenderFillRect(renderer, &rect_nom);//ICI
  SDL_RenderFillRect(renderer, &rect_level);//ICI
  SDL_RenderFillRect(renderer, &rect_pdv);//ICI
  SDL_RenderFillRect(renderer, &rect_att);//ICI
  SDL_RenderFillRect(renderer, &rect_def);//ICI


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderDrawRect(renderer, &rect_reprendre);
	SDL_RenderDrawRect(renderer, &rect_options);
	SDL_RenderDrawRect(renderer, &rect_quitter);

  SDL_RenderDrawRect(renderer, &rect_nom);//ICI
  SDL_RenderDrawRect(renderer, &rect_level);//ICI
  SDL_RenderDrawRect(renderer, &rect_pdv);//ICI
  SDL_RenderDrawRect(renderer, &rect_att);//ICI
  SDL_RenderDrawRect(renderer, &rect_def);//ICI



	creerTexte(renderer, police, "REPRENDRE", WIDTH/2 - 7 * 21, rect_reprendre.y - 5);
	creerTexte(renderer, police, "OPTIONS", WIDTH/2 - 7 * 17, rect_options.y - 5);
	creerTexte(renderer, police, "QUITTER", WIDTH/2 - 7 * 18, rect_quitter.y - 5);

  creerTexte(renderer, police_stats, "NOM", WIDTH/28, rect_nom.y-3); //ICI se place à gauche
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


  creerTexte(renderer, police_stats, player->nom, WIDTH/28*6, rect_nom.y+10); //ICI Ce place à l'opposé de la case
  creerTexte(renderer, police_stats, level, WIDTH/28*6, rect_level.y+10); //ICI
  creerTexte(renderer, police_stats, pdv, WIDTH/28*6, rect_pdv.y+10); //ICI
  creerTexte(renderer, police_stats, att, WIDTH/28*6, rect_att.y+10); //ICI
  creerTexte(renderer, police_stats, def, WIDTH/28*6, rect_def.y+10); //ICI*/

 	SDL_RenderPresent(renderer);

    SDL_Event event;
	SDL_bool pause_launched = SDL_TRUE;
	SDL_bool reprendre_asked = SDL_FALSE;
	SDL_bool options_asked = SDL_FALSE;
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
							options_asked = SDL_TRUE;
							pause_launched = SDL_FALSE;
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

    if (reprendre_asked)
		printf("Reprendre");
	else if (options_asked)
		printf("Options");
	else if (quitter_asked)
		printf("Quitter");

}
