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
			if( pos->y + 1 + pos->h / TAILLE_BLOCK <= MAP_MAX_Y )
				pos->y++;

			break;

		case HAUT:
			if( pos->y - 1 >= 0 )
				pos->y--;
			break;

		case DROITE:
			if(pos->x + 1 + pos->w / TAILLE_BLOCK <= MAP_MAX_X)
				pos->x++;
			break;

		case GAUCHE:
			if(pos->x - 1 >= 0)
				pos->x--;
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
 * \fn void attaque(int carte[][MAP_MAX_X], SDL_Rect *srcPos, SDL_Rect *destPos, int direction, SDL_Renderer *render, int rangeAttaque, t_pers *srcatt, t_pers *destatt)
 * \brief Fonction d'attaque du jeu.
 */
void attaque(int carte[][MAP_MAX_X], SDL_Rect *srcPos, SDL_Rect *destPos, int direction, SDL_Renderer *render, int rangeAttaque, t_pers *srcatt, t_pers *destatt)
{
	switch(direction)
	{
		case BAS:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcatt->att - destatt->def > 0)
					destatt->pdv -= (srcatt->att - destatt->def);
				mouvement(carte, destPos, BAS, render); //Simulation d'un knockback
			}
			break;

		case HAUT:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcatt->att - destatt->def > 0)
					destatt->pdv -= (srcatt->att - destatt->def);
				mouvement(carte, destPos, HAUT, render); //Simulation d'un knockback
			}
			break;

		case DROITE:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcatt->att - destatt->def > 0)
					destatt->pdv -= (srcatt->att - destatt->def);
				mouvement(carte, destPos, DROITE, render); //Simulation d'un knockback
			}
			break;

		case GAUCHE:
			if(hitMarker(direction, srcPos, destPos, rangeAttaque))
			{
				if (srcatt->att - destatt->def > 0)
					destatt->pdv -= (srcatt->att - destatt->def);
				mouvement(carte, destPos, GAUCHE, render); //Simulation d'un knockback
			}
			break;
	}

	SDL_RenderClear(render);
}

/**
 * \fn int botActions(int carte[][MAP_MAX_X], SDL_Rect *botTueur, SDL_Rect *joueur, SDL_Renderer *render, t_pers *srcatt, t_pers *destatt)
 * \brief Fonction concernant les actions du/des bots.
 * \return Côté vers lequel le bot se tourne.
 */
int botActions(int carte[][MAP_MAX_X], SDL_Rect *botTueur, SDL_Rect *joueur, SDL_Renderer *render, t_pers *srcatt, t_pers *destatt)
{
	if (botTueur->x == joueur->x) //Joueur et bot sur la même horizontale
	{
		if(joueur->y > botTueur->y) //Joueur en dessous du bot
		{
			if(joueur->y - botTueur->y <= RANGE_BOT)
				attaque(carte, botTueur, joueur, BAS, render, RANGE_BOT, srcatt, destatt);
			else
			{
				mouvement(carte, botTueur, BAS, render);
				return BAS;
			}
		}
		else //Joueur au dessus du bot
		{
			if(botTueur->y - joueur->y <= RANGE_BOT)
				attaque(carte, botTueur, joueur, HAUT, render, RANGE_BOT, srcatt, destatt);
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
				attaque(carte, botTueur, joueur, DROITE, render, RANGE_BOT, srcatt, destatt);
			else
			{
				mouvement(carte, botTueur, DROITE, render);
				return DROITE;
			}
		}
		else //Joueur à gauche du bot
		{
			if(botTueur->x - joueur->x <= RANGE_BOT)
				attaque(carte, botTueur, joueur, GAUCHE, render, RANGE_BOT, srcatt, destatt);
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

int canChangeMap(SDL_Rect *joueur, int direction, t_pers *persBot)
{
	switch (direction)
	{
		case HAUT:
			return (
				( joueur->x == (MAP_MAX_X/2) - 1 || joueur->x == MAP_MAX_X/2 )
				&& (joueur->y - 1 < 0)
				&& (persBot->alive == 0)
				&& (persBot->faction == MECHANT)
			);
			break;

		case BAS:
			return (
				( joueur->x == (MAP_MAX_X/2) - 1 || joueur->x == MAP_MAX_X/2 )
				&& (joueur->y + (joueur->h / TAILLE_BLOCK) + 1 > MAP_MAX_Y)
				&& (persBot->alive == 0)
				&& (persBot->faction == MECHANT)
			);
			break;

		case GAUCHE:
			return (
				(joueur->y == (MAP_MAX_Y/2) - 1 || joueur->y == MAP_MAX_Y/2 )
				&& (joueur->x - 1 < 0)
				&& (persBot->alive == 0)
				&& (persBot->faction == MECHANT)
			);
			break;

		case DROITE:
			return (
				(joueur->y == (MAP_MAX_Y/2) - 1 || joueur->y == MAP_MAX_Y/2 )
				&& (joueur->x + (joueur->h / TAILLE_BLOCK) + 1 > MAP_MAX_X)
				&& (persBot->alive == 0)
				&& (persBot->faction == MECHANT)
			);
			break;
	}
	return 0;
}

void changementMap(SDL_Rect *joueur, SDL_Rect *bot, int direction)
{
	switch (direction)
	{
		case HAUT:
			joueur->y = MAP_MAX_Y - (joueur->h / TAILLE_BLOCK);

			bot->x = (MAP_MAX_X / 2);
			bot->y = 0;
			break;

		case BAS:
			joueur->y = 0;

			bot->x = (MAP_MAX_X / 2);
			bot->y = MAP_MAX_Y - (joueur->h / TAILLE_BLOCK);
			break;

		case GAUCHE:
			joueur->x = MAP_MAX_X - (joueur->w / TAILLE_BLOCK);

			bot->x = 0;
			bot->y = (MAP_MAX_Y / 2);
			break;

		case DROITE:
			joueur->x = 0;

			bot->x = MAP_MAX_X - (bot->w / TAILLE_BLOCK);
			bot->y = (MAP_MAX_Y / 2);
			break;
	}
}

/**
 * \fn void jouer(SDL_Renderer *render , SDL_Window *window)
 * \brief Fonction principale du jeu.
 */
void jouer(SDL_Renderer *render , SDL_Window *window)
{

/**-------------------------Définition des textes-------------------------**/
	///Définition des polices
	int taille_mort = 128;
	int taille_hp = 48;

	TTF_Font *police_mort = TTF_OpenFont(NOM_FONT, taille_mort);
	TTF_Font *police_hp = TTF_OpenFont(NOM_FONT, taille_hp);

	if (!police_mort)
		SDL_ExitWithError("Erreur du chargement de la police_mort", window, render, NULL);

	if (!police_hp)
		SDL_ExitWithError("Erreur du chargement de la police_hp", window, render, NULL);

	//Définition des couleurs

	SDL_Color RED = {220, 0, 0};

/**-------------------------Initialisation personnage-------------------------**/

	///On crée des variables
	SDL_Rect position, positionJoueur, positionBot, positionB;

	SDL_Surface *sPerso[4] = {NULL};
	SDL_Texture *tPerso[4] = {NULL};

	SDL_Surface *sPersoatt[4] = {NULL};
	SDL_Texture *tPersoatt[4] = {NULL};

	SDL_Surface *sBot[4] = {NULL};
	SDL_Texture *tBot[4] = {NULL};

	SDL_Surface *sStuff[9] = {NULL};
	SDL_Texture *tStuff[9] = {NULL};

	SDL_Texture *persoActuel = NULL;
	SDL_Texture *botTueur = NULL;

	t_pers *persPlayer;
	t_pers *persBotTueur; //t_pers *persBotTueur[x] avec x = nombre de bots

	t_objet *itemDrop; //t_objet *itemDrop[x] avec x = nombre de bots

	t_stuff playerStuff;

	//initialisation de l'inventaire (vide en début de partie)
	playerStuff.head = NULL;
	playerStuff.chest = NULL;
	playerStuff.gloves = NULL;
	playerStuff.legs = NULL;
	playerStuff.feet = NULL;
	playerStuff.main_hand = NULL;
	playerStuff.off_hand = NULL;

	///Compteur_Variable
	int i;
	int botSide;
	int cptBot, cptJoueur;
	cptBot = cptJoueur = 0;

	int player_recent_attack = 0;

	char texte_life[5];

	///Definit les images sur les Surfaces Perso[Orientation]
	sPerso[HAUT] = IMG_Load("images/player/stickmanG.png");
	sPerso[BAS] = IMG_Load("images/player/stickmanD.png");
	sPerso[GAUCHE] = IMG_Load("images/player/stickmanG.png");
	sPerso[DROITE] = IMG_Load("images/player/stickmanD.png");

	sPersoatt[HAUT] = IMG_Load("images/player/stickmanG_attack.png");
	sPersoatt[BAS] = IMG_Load("images/player/stickmanD_attack.png");
	sPersoatt[GAUCHE] = IMG_Load("images/player/stickmanG_attack.png");
	sPersoatt[DROITE] = IMG_Load("images/player/stickmanD_attack.png");

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
	sStuff[HEART] = IMG_Load("images/stuff/heart.png");
	sStuff[HALF_HEART] = IMG_Load("images/stuff/half_heart.png");

	///Définition de la carte
	int carte[MAP_MAX_Y][MAP_MAX_X];

	for(i = 0; i < 4; i++)
	{
		if(sPerso[i] == NULL)
			SDL_ExitWithError("image personnage", window, render, NULL);

		if(sPersoatt[i] == NULL)
			SDL_ExitWithError("image personnage attaque", window, render, NULL);

		if(sBot[i] == NULL)
			SDL_ExitWithError("image bot", window, render, NULL);
	}

	for(i = 0; i < 4; i++)
	{
		tPerso[i] = SDL_CreateTextureFromSurface(render, sPerso[i]);
		SDL_FreeSurface(sPerso[i]);

		tPersoatt[i] = SDL_CreateTextureFromSurface(render, sPersoatt[i]);
		SDL_FreeSurface(sPersoatt[i]);

		tBot[i] = SDL_CreateTextureFromSurface(render, sBot[i]);
		SDL_FreeSurface(sBot[i]);
	}

	for(i = 0; i < 9; i++)
	{
		if(sStuff[i] == NULL)
			SDL_ExitWithError("image stuff", window, render, NULL);

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

	///Taille et position des bots/joueur

	positionJoueur.w = positionBot.w = 3*TAILLE_BLOCK;
	positionJoueur.h = positionBot.h = positionJoueur.w;

	position.w = positionB.w = 3*TAILLE_BLOCK;
	position.h = positionB.h = position.w;

	positionJoueur.x = 0;
	positionJoueur.y = 0;

	positionBot.x = (MAP_MAX_X - (positionJoueur.x + (positionB.w / TAILLE_BLOCK )));
	positionBot.y = (MAP_MAX_Y - (positionJoueur.y + (positionB.h / TAILLE_BLOCK )));

	///Création du joueur et du/des bots
	persPlayer = crea_pers(GENTIL, DEFAULT_LEVEL);
	persBotTueur = crea_pers(MECHANT, DEFAULT_LEVEL);

	///Gestion des FPS
	unsigned int frameLimit = SDL_GetTicks() + 16;

/**-------------------------Programme principal du jeu-------------------------**/

	SDL_bool run = SDL_TRUE;
	SDL_Event event;

	/* Cache le curseur de la souris */
	SDL_ShowCursor(SDL_DISABLE);

	SDL_Rect zone_jeu;
	zone_jeu.w = MAP_MAX_X * TAILLE_BLOCK;
	zone_jeu.h = MAP_MAX_Y * TAILLE_BLOCK;
	zone_jeu.x = 0;
	zone_jeu.y = 0;

	SDL_Rect rect_case;

	rect_case.w = rect_case.h = TAILLE_BLOCK;
	rect_case.x = rect_case.y = 0;

	while(run)
	{

		const Uint8* keystate = SDL_GetKeyboardState(NULL); //Regarde si la touche est restée enfoncée (pour effectuer des mouvements plus fluides)
		SDL_PumpEvents();

		if(cptJoueur == 2)
		{
			if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_W])
			{
				if (canChangeMap(&positionJoueur, GAUCHE, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, GAUCHE);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else if(canChangeMap(&positionJoueur, HAUT, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, HAUT);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, GAUCHE, render);
					mouvement(carte, &positionJoueur, HAUT, render);
				}

				if (player_recent_attack == 0)
					persoActuel = tPerso[GAUCHE];
			}
			else if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_S])
			{
				if (canChangeMap(&positionJoueur, GAUCHE, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, GAUCHE);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else if(canChangeMap(&positionJoueur, BAS, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, BAS);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, GAUCHE, render);
					mouvement(carte, &positionJoueur, BAS, render);
				}
				if (player_recent_attack == 0)
					persoActuel = tPerso[GAUCHE];
			}
			else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_W])
			{
				if (canChangeMap(&positionJoueur, DROITE, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, DROITE);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else if(canChangeMap(&positionJoueur, HAUT, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, HAUT);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, DROITE, render);
					mouvement(carte, &positionJoueur, HAUT, render);
				}
				if (player_recent_attack == 0)
					persoActuel = tPerso[DROITE];
			}
			else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_S])
			{
				if (canChangeMap(&positionJoueur, DROITE, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, DROITE);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else if(canChangeMap(&positionJoueur, BAS, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, BAS);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, DROITE, render);
					mouvement(carte, &positionJoueur, BAS, render);
				}
				if (player_recent_attack == 0)
					persoActuel = tPerso[DROITE];
			}
			else if (keystate[SDL_SCANCODE_S])
			{
				if(canChangeMap(&positionJoueur, BAS, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, BAS);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, BAS, render);
				}
				//persoActuel = tPerso[BAS];
			}
			else if (keystate[SDL_SCANCODE_W])
			{
				if(canChangeMap(&positionJoueur, HAUT, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, HAUT);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, HAUT, render);
				}
				//persoActuel = tPerso[HAUT];
			}
			else if (keystate[SDL_SCANCODE_D])
			{
				if(canChangeMap(&positionJoueur, DROITE, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, DROITE);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, DROITE, render);
				}

				if (player_recent_attack == 0)
					persoActuel = tPerso[DROITE];
			}
			else if (keystate[SDL_SCANCODE_A])
			{
				if(canChangeMap(&positionJoueur, GAUCHE, persBotTueur))
				{
					changementMap(&positionJoueur, &positionBot, GAUCHE);
					free(itemDrop);
					free(persBotTueur);
					persBotTueur = crea_pers(persBotTueur->faction, persBotTueur->lvl);
				}
				else
				{
					mouvement(carte, &positionJoueur, GAUCHE, render);
				}

				if (player_recent_attack == 0)
					persoActuel = tPerso[GAUCHE];
			}
			cptJoueur = 0;
		}
		else
			cptJoueur++;

		//Gestion de l'animation de l'attaque
		if (player_recent_attack > 0)
		{
			player_recent_attack--;
			if (player_recent_attack == 0)
			{
				if(persoActuel == tPersoatt[GAUCHE])
					persoActuel = tPerso[GAUCHE];
				else if(persoActuel == tPersoatt[DROITE])
					persoActuel = tPerso[DROITE];
				else if(persoActuel == tPersoatt[HAUT])
					persoActuel = tPerso[HAUT];
				else if(persoActuel == tPersoatt[BAS])
					persoActuel = tPerso[BAS];
			}
		}

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
							SDL_ShowCursor(SDL_ENABLE);
							run = menu_pause(window, render, persPlayer, playerStuff);
							SDL_ShowCursor(SDL_DISABLE);
							break;

						case SDLK_n:
							printf("Respawn\n");
							persBotTueur = crea_pers(MECHANT, DEFAULT_LEVEL);
							break;

						///Attaques
						case SDLK_UP:
							attaque(carte, &positionJoueur, &positionBot, HAUT, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							player_recent_attack = 20;
							persoActuel = tPersoatt[HAUT];
							break;
						case SDLK_LEFT:
							attaque(carte, &positionJoueur, &positionBot, GAUCHE, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							player_recent_attack = 20;
							persoActuel = tPersoatt[GAUCHE];
							break;
						case SDLK_DOWN:
							attaque(carte, &positionJoueur, &positionBot, BAS, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							player_recent_attack = 20;
							persoActuel = tPersoatt[BAS];
							break;
						case SDLK_RIGHT:
							attaque(carte, &positionJoueur, &positionBot, DROITE, render, RANGE_JOUEUR, persPlayer, persBotTueur);
							player_recent_attack = 20;
							persoActuel = tPersoatt[DROITE];
							break;

						default:
							break;
					}

				default:
					break;

			}
		}

		if(persBotTueur->alive)
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

		//Affichage des mouvements par le joueur et les ennemis
		position.x = positionJoueur.x * TAILLE_BLOCK;
		position.y = positionJoueur.y * TAILLE_BLOCK;

		SDL_RenderClear(render);

		//Dessin de la map
		SDL_SetRenderDrawColor(render, 0, 255, 255, 220);
		rect_case.y = 0; rect_case.x = 12 * TAILLE_BLOCK; SDL_RenderFillRect(render, &rect_case);
		rect_case.y = 0; rect_case.x = 13 * TAILLE_BLOCK; SDL_RenderFillRect(render, &rect_case);

		rect_case.y = 25 * TAILLE_BLOCK; rect_case.x = 12 * TAILLE_BLOCK; SDL_RenderFillRect(render, &rect_case);
		rect_case.y = 25 * TAILLE_BLOCK; rect_case.x = 13 * TAILLE_BLOCK; SDL_RenderFillRect(render, &rect_case);

		rect_case.y = 12 * TAILLE_BLOCK; rect_case.x = 0; SDL_RenderFillRect(render, &rect_case);
		rect_case.y = 13 * TAILLE_BLOCK; rect_case.x = 0; SDL_RenderFillRect(render, &rect_case);

		rect_case.y = 12 * TAILLE_BLOCK; rect_case.x = 25 * TAILLE_BLOCK; SDL_RenderFillRect(render, &rect_case);
		rect_case.y = 13 * TAILLE_BLOCK; rect_case.x = 25 * TAILLE_BLOCK; SDL_RenderFillRect(render, &rect_case);

		SDL_SetRenderDrawColor(render, 0, 220, 0, 100);
		for(i = 0; i <= MAP_MAX_Y; i++){
			for(int j = 0; j < MAP_MAX_X; j++){
				rect_case.x = j * TAILLE_BLOCK;
				SDL_RenderDrawRect(render, &rect_case);
			}
			rect_case.y = i * TAILLE_BLOCK;
		}
		SDL_SetRenderDrawColor(render, 220, 0, 0, 150);
		SDL_RenderDrawRect(render, &zone_jeu);
		SDL_SetRenderDrawColor(render, 200, 10, 200, 220);
		SDL_RenderDrawRect(render, &position);
		SDL_SetRenderDrawColor(render, P_R, P_G, P_B, 255);


		//Affichage de la vie en haut à gauche
		if (persPlayer->pdv > 0){
			//itoa(persPlayer->pdv, texte_life, 10); //spécifique windows
			sprintf(texte_life,"%d",persPlayer->pdv); //marche sur tous les OS
			creerTexte(render, police_hp, texte_life, 10, 10, RED);
		}

		if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0)
			SDL_Log("Erreur lors de l'affichage à l'écran");

		if(persBotTueur->alive)
		{
			positionB.x = positionBot.x * TAILLE_BLOCK;
			positionB.y = positionBot.y * TAILLE_BLOCK;

			if(SDL_RenderCopy(render, botTueur, NULL, &positionB) != 0)
				SDL_Log("Erreur lors de l'affichage à l'écran");
		}

		//Gestion du drop lorsqu'un ennemi meurt
		if (persBotTueur->alive == 1 && persBotTueur->pdv <= 0)
		{
			persBotTueur->alive = 0;
			itemDrop = drop(persBotTueur->lvl);
		}

		if (persBotTueur->alive == 0 && itemDrop != NULL)
			affiche_drop(render, &positionB, tStuff, itemDrop);

		if (itemDrop != NULL && recupere_drop(&positionJoueur, &positionBot, itemDrop, &playerStuff, persPlayer))
			itemDrop = NULL;

		if (persPlayer->pdv <= 0){
			persPlayer->alive = 0;
			run = SDL_FALSE;

			int widthTemp, heightTemp;
			TTF_SizeText(police_mort, "YOU DIED", &widthTemp, &heightTemp);
			creerTexte(render, police_mort, "YOU DIED", WIDTH/2 - widthTemp/2, HEIGHT/2 - heightTemp/2, RED);

			SDL_RenderPresent(render);
			SDL_Delay(3000);
		}

		///Gestion des 60 fps (1000ms/60 = 16.6 -> 16
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;

		SDL_RenderPresent(render);
	}
	/* Affiche le curseur de la souris */
	SDL_ShowCursor(SDL_ENABLE);

	SDL_DestroyTexture(*tPerso);
	SDL_DestroyTexture(*tBot);
	SDL_DestroyTexture(*tStuff);

	SDL_DestroyTexture(persoActuel);
	SDL_DestroyTexture(botTueur);

	free(persBotTueur);
	persBotTueur = NULL;
	free(persPlayer);
	persPlayer = NULL;

	free(police_mort);
	free(police_hp);
}
