/**
 * \file jeu.c
 * \brief Contient les actions disponibles pendant une partie
 * \author TACHET Nicolas, SANNA Florian
 * \version 1.0
 * \date 2021
 */

#include "commun.h"

/**
 * \fn void mouvement(int carte[][MAP_MAX_X], SDL_Rect *pos, int direction, SDL_Renderer *render)
 * \brief Bouge le SDL_Rect (correspondant à un personnage) passé en paramètre.
 */
void mouvement(int carte[][MAP_MAX_X], SDL_Rect *pos, int direction, SDL_Renderer *render)
{
	switch(direction)
	{
		case BAS:
			if( pos->y + pos->h/TAILLE_BLOCK <= MAP_MAX_Y )
				pos->y++;
			break;

		case HAUT:
			if(pos->y > 0)
				pos->y--;
			break;

		case DROITE:
			if(pos->x + pos->w/TAILLE_BLOCK <= MAP_MAX_X)
				pos->x++;
			break;

		case GAUCHE:
			if(pos->x > 0)
				pos->x--;
			break;

		default:
			break;
	}

	SDL_RenderClear(render);
}

/**
 * \fn int hitMarker(int direction, SDL_Rect *srcPos, SDL_Rect *destPos, int rangeAttaque)
 * \brief Regarde si une attaque peut être effectuée.
 * \return 1 si l'attaque peut être effectuée, 0 sinon.
 */
int hitMarker(int direction, SDL_Rect *srcPos, SDL_Rect *destPos, int rangeAttaque)
{
	for (int i = 0; i <= rangeAttaque; i++)
	{
		if (direction == BAS)
		{
			if ((srcPos->x == destPos->x) && ((srcPos->y + i) == destPos->y))
				return 1;
		}
		else if (direction == HAUT)
		{
			if ((srcPos->x == destPos->x) && ((srcPos->y - i) == destPos->y))
				return 1;
		}
		else if (direction == DROITE)
		{
			if ((srcPos->y == destPos->y) && ((srcPos->x + i) == destPos->x))
				return 1;
		}
		else if (direction == GAUCHE)
		{
			if ((srcPos->y == destPos->y) && ((srcPos->x - i) == destPos->x))
				return 1;
		}
	}
	return 0;
}

/**
 * \fn void attaque(int carte[][MAP_MAX_X], SDL_Rect *srcPos, SDL_Rect *destPos, int direction, SDL_Renderer *render, int rangeAttaque, t_pers *srcAtq, t_pers *destAtq)
 * \brief Fonction d'attaque du jeu.
 */
void attaque(int carte[][MAP_MAX_X], SDL_Rect *srcPos, SDL_Rect *destPos, int direction, SDL_Renderer *render, int rangeAttaque, t_pers *srcAtq, t_pers *destAtq)
{
	switch(direction)
	{  
		case BAS:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcAtq->atq - destAtq->def > 0)
					destAtq->pdv -= (srcAtq->atq - destAtq->def);
				mouvement(carte, destPos, BAS, render); //Simulation d'un knockback
			}
			break;
 
		case HAUT:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcAtq->atq - destAtq->def > 0)
					destAtq->pdv -= (srcAtq->atq - destAtq->def);
				mouvement(carte, destPos, HAUT, render); //Simulation d'un knockback
			}
			break;
 
		case DROITE:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcAtq->atq - destAtq->def > 0)
					destAtq->pdv -= (srcAtq->atq - destAtq->def);
				mouvement(carte, destPos, DROITE, render); //Simulation d'un knockback
			}
			break;
 
		case GAUCHE:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcAtq->atq - destAtq->def > 0)
					destAtq->pdv -= (srcAtq->atq - destAtq->def);
				mouvement(carte, destPos, GAUCHE, render); //Simulation d'un knockback
			}
			break;
 
		default:
			break;
	}
		
	SDL_RenderClear(render);
}

/**
 * \fn int botActions(int carte[][MAP_MAX_X], SDL_Rect *botTueur, SDL_Rect *joueur, SDL_Renderer *render, t_pers *srcAtq, t_pers *destAtq)
 * \brief Fonction concernant les actions du/des bots.
 * \return Côté vers lequel le bot se tourne.
 */
int botActions(int carte[][MAP_MAX_X], SDL_Rect *botTueur, SDL_Rect *joueur, SDL_Renderer *render, t_pers *srcAtq, t_pers *destAtq)
{
	if (botTueur->x == joueur->x) //Joueur et bot sur la même horizontale
	{
		if(joueur->y > botTueur->y) //Joueur en dessous du bot
		{
			if(joueur->y - botTueur->y <= RANGE_BOT)
				attaque(carte, botTueur, joueur, BAS, render, RANGE_BOT, srcAtq, destAtq);
			else
			{
				mouvement(carte, botTueur, BAS, render);
				return BAS;
			}
		}
		else //Joueur au dessus du bot
		{
			if(botTueur->y - joueur->y <= RANGE_BOT)
				attaque(carte, botTueur, joueur, HAUT, render, RANGE_BOT, srcAtq, destAtq);
			else
			{
				mouvement(carte, botTueur, HAUT, render);
				return HAUT;
			}
		}
	}
	else if (botTueur->y == joueur->y) //Joueur et bot sur la même verticale
	{
		if(joueur->x > botTueur->x) //Joueur à droite du bot
		{
			if(joueur->x - botTueur->x <= RANGE_BOT)
				attaque(carte, botTueur, joueur, DROITE, render, RANGE_BOT, srcAtq, destAtq);
			else
			{
				mouvement(carte, botTueur, DROITE, render);
				return DROITE;
			}
		}
		else //Joueur à gauche du bot
		{
			if(botTueur->x - joueur->x <= RANGE_BOT)
				attaque(carte, botTueur, joueur, GAUCHE, render, RANGE_BOT, srcAtq, destAtq);
			else
			{
				mouvement(carte, botTueur, GAUCHE, render);
				return GAUCHE;
			}
		}
	}
	else if(joueur->x > botTueur->x) //Joueur à droite du bot
	{
		if(joueur->y > botTueur->y) //Joueur en dessous du bot
		{
			if(joueur->y - botTueur->y > joueur->x - botTueur->x) //Joueur en dessous à droite du bot (proche en x)
			{
				mouvement(carte, botTueur, BAS, render);
				return BAS;
			}
			else
			{
				mouvement(carte, botTueur, DROITE, render);
				return DROITE;
			}
		}
		else //Joueur au dessus du bot
		{
			if(botTueur->y - joueur->y > joueur->x - botTueur->x) //Joueur au dessus à droite du bot (proche en x)
			{	
				mouvement(carte, botTueur, HAUT, render);
				return HAUT;
			}
			else
			{
				mouvement(carte, botTueur, DROITE, render);
				return DROITE;
			}
		}
	}
	else //Joueur à gauche du bot
	{
		if(joueur->y > botTueur->y) //Joueur en dessous du bot
		{
			if(joueur->y - botTueur->y > botTueur->x - joueur->x) //Joueur en dessous à gauche du bot (proche en x)
			{	
				mouvement(carte, botTueur, BAS, render);
				return BAS;
			}
			else
			{
				mouvement(carte, botTueur, GAUCHE, render);
				return GAUCHE;
			}
		}
		else //Joueur au dessus du bot
		{
			if(botTueur->y - joueur->y > joueur->x - botTueur->x) //Joueur au dessus à droite du bot (proche en x)
			{
				mouvement(carte, botTueur, HAUT, render);
				return HAUT;
			}
			else
			{
				mouvement(carte, botTueur, GAUCHE, render);
				return GAUCHE;
			}
		}
	}
}

/**
 * \fn void jouer(SDL_Renderer *render , SDL_Window *window)
 * \brief Fonction principale du jeu.
 */
void jouer(SDL_Renderer *render , SDL_Window *window)
{
/**-------------------------Initialisation personnage-------------------------**/

	///On crée des variables
	SDL_Rect position, positionJoueur, positionBot, positionB;

	SDL_Surface *sPerso[4] = {NULL};
	SDL_Texture *tPerso[4] = {NULL};

	SDL_Surface *sBot[4] = {NULL};
	SDL_Texture *tBot[4] = {NULL};

	SDL_Surface *sStuff[7] = {NULL};
	SDL_Texture *tStuff[7] = {NULL};
		
	SDL_Texture *persoActuel = NULL;
	SDL_Texture *botTueur = NULL;

	t_pers *persPlayer;
	t_pers *persBotTueur;

	t_objet *itemDrop;

	///Compteur_Variable
	int i;
	int botSide;
	int cptBot, cptJoueur;
	cptBot = cptJoueur = 0;

	///Definit les images sur les Surfaces Perso[Orientation]
	sPerso[HAUT] = IMG_Load("images/player/stickmanG.png");
	sPerso[BAS] = IMG_Load("images/player/stickmanD.png");
	sPerso[GAUCHE] = IMG_Load("images/player/stickmanG.png");
	sPerso[DROITE] = IMG_Load("images/player/stickmanD.png");

	sBot[HAUT] = IMG_Load("images/mobs/bot_de_la_mort_qui_tueG.png");
	sBot[BAS] = IMG_Load("images/mobs/bot_de_la_mort_qui_tueD.png");
	sBot[GAUCHE] = IMG_Load("images/mobs/bot_de_la_mort_qui_tueG.png");
	sBot[DROITE] = IMG_Load("images/mobs/bot_de_la_mort_qui_tueD.png");

	sStuff[HEAD] = IMG_Load("images/stuff/head.png");
	sStuff[CHEST] = IMG_Load("images/stuff/chest.png");
	sStuff[GLOVES] = IMG_Load("images/stuff/gloves.png");
	sStuff[LEGS] = IMG_Load("images/stuff/legs.png");
	sStuff[FEET] = IMG_Load("images/stuff/feet.png");
	sStuff[MAIN_HAND] = IMG_Load("images/stuff/main_hand.png");
	sStuff[OFF_HAND] = IMG_Load("images/stuff/off_hand.png");

	///Définition de la carte
	int carte[MAP_MAX_Y][MAP_MAX_X];

	for(i = 0; i < 4; i++)
	{  
		if(sPerso[i] == NULL)
			SDL_ExitWithError("image personnage", window, render, NULL);
		
		if(sBot[i] == NULL)
			SDL_ExitWithError("image bot", window, render, NULL);

		if(sStuff[i] == NULL)
			SDL_ExitWithError("image stuff", window, render, NULL);
	}

	for(i = 0; i < 4; i++)
	{
		tPerso[i] = SDL_CreateTextureFromSurface(render, sPerso[i]);
		SDL_FreeSurface(sPerso[i]);

		tBot[i] = SDL_CreateTextureFromSurface(render, sBot[i]);
		SDL_FreeSurface(sBot[i]);
	}

	for(i = 0; i < 7; i++)
	{
		tStuff[i] = SDL_CreateTextureFromSurface(render, sStuff[i]);
		SDL_FreeSurface(sStuff[i]);
	}

	///On remet le render vierge
	SDL_RenderClear(render);
 
	///Définission de la position du joueur et du bot
	persoActuel = tPerso[HAUT];
	if(persoActuel == NULL)
		SDL_Log("Erreur persoActuel");
		
	botTueur = tBot[HAUT];
	if(botTueur == NULL)
		SDL_Log("Erreur botTueur");

	positionJoueur.x = 3;
	positionJoueur.y = 3;

	positionBot.x = (MAP_MAX_X-positionJoueur.x);
	positionBot.y = (MAP_MAX_Y-positionJoueur.y);

	positionJoueur.w = positionBot.w = 100;
	positionJoueur.h = positionBot.h = 100;

	position.w = positionB.w = 100;
	position.h = positionB.h = 100;

	///Création du joueur et du/des bots
	persPlayer = crea_pers(MECHANT, DEFAULT_LEVEL);
	persBotTueur = crea_pers(MECHANT, DEFAULT_LEVEL);

	///Gestion des FPS
	unsigned int frameLimit = SDL_GetTicks() + 16;

/**-------------------------Programme principal du jeu-------------------------**/

	SDL_bool run = SDL_TRUE;
	SDL_Event event;

	/* Cache le curseur de la souris */
	SDL_ShowCursor(SDL_DISABLE);

	while(run)
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL); //Regarde si la touche est restée enfoncée (pour effectuer des mouvements plus fluides)
		SDL_PumpEvents();

		if(cptJoueur == 2)
		{
			if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_W])
			{
				mouvement(carte, &positionJoueur, GAUCHE, render);
				mouvement(carte, &positionJoueur, HAUT, render);
				persoActuel = tPerso[GAUCHE];
			}
			else if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_S])
			{
				mouvement(carte, &positionJoueur, GAUCHE, render);
				mouvement(carte, &positionJoueur, BAS, render);
				persoActuel = tPerso[GAUCHE];
			}
			else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_W])
			{
				mouvement(carte, &positionJoueur, DROITE, render);
				mouvement(carte, &positionJoueur, HAUT, render);
				persoActuel = tPerso[DROITE];
			}
			else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_S])
			{
				mouvement(carte, &positionJoueur, DROITE, render);
				mouvement(carte, &positionJoueur, BAS, render);
				persoActuel = tPerso[DROITE];
			}
			else if (keystate[SDL_SCANCODE_S])
			{
				mouvement(carte, &positionJoueur, BAS, render);
				//persoActuel = tPerso[BAS];
			}
			else if (keystate[SDL_SCANCODE_W])
			{
				mouvement(carte, &positionJoueur, HAUT, render);
				//persoActuel = tPerso[HAUT];
			}
			else if (keystate[SDL_SCANCODE_D])
			{
				mouvement(carte, &positionJoueur, DROITE, render);
				persoActuel = tPerso[DROITE];
			}
			else if (keystate[SDL_SCANCODE_A])
			{
				mouvement(carte, &positionJoueur, GAUCHE, render);
				persoActuel = tPerso[GAUCHE];
			}
			cptJoueur = 0;
		}
		else
			cptJoueur++;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{  
				case SDL_QUIT:
					run = SDL_FALSE;
					break;
 
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							SDL_RenderPresent(render);
							printf("Le jeu est désormais en pause.\n");
							run = menu_pause(window, render);
							break;

						///Attaques
						case SDLK_UP:
							attaque(carte, &positionJoueur, &positionBot, HAUT, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							break;
						case SDLK_LEFT:
							attaque(carte, &positionJoueur, &positionBot, GAUCHE, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							break;
						case SDLK_DOWN:
							attaque(carte, &positionJoueur, &positionBot, BAS, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							break;
						case SDLK_RIGHT:
							attaque(carte, &positionJoueur, &positionBot, DROITE, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							break;
						
						default:
							break;
					}
 
				default:
					break;
 
			}
		}

		if(persBotTueur->pdv > 0)
		{
			if(cptBot == 6)
			{
				botSide = botActions(carte, &positionBot, &positionJoueur, render, persBotTueur, persPlayer);
				botTueur = tBot[botSide];
				cptBot = 0;
			}
			else
				cptBot++;
		}
		if (persBotTueur->alive == 1 && persBotTueur->pdv <= 0)
		{
			persBotTueur->alive = 0;
			itemDrop = drop(persBotTueur->lvl);
			if(itemDrop != NULL)
			{
				affiche_drop(render, &positionB, tStuff, itemDrop);
				printf("Affiche drop\n");
			}
		}
		if (persBotTueur->alive == 0)
			affiche_drop(render, &positionB, tStuff, itemDrop);

		position.x = positionJoueur.x * TAILLE_BLOCK;
		position.y = positionJoueur.y * TAILLE_BLOCK;

		if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0)
			SDL_Log("Erreur lors de l'affichage à l'écran");
		
		if(persBotTueur->pdv > 0)
		{
			positionB.x = positionBot.x * TAILLE_BLOCK;
			positionB.y = positionBot.y * TAILLE_BLOCK;

			if(SDL_RenderCopy(render, botTueur, NULL, &positionB) != 0)
				SDL_Log("Erreur lors de l'affichage à l'écran");
		}

		///Gestion des 60 fps (1000ms/60 = 16.6 -> 16 
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;

		SDL_RenderPresent(render);
   		
	}
	/* Affiche le curseur de la souris */
	SDL_ShowCursor(SDL_ENABLE);
	destruction_pers(persBotTueur);
	destruction_pers(persPlayer);
}
 
