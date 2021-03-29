#include "commun.h"

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

void attaque(int carte[][MAP_MAX_X], SDL_Rect *pos , int direction, SDL_Renderer *render, int rangeAttaque)
{
  
    switch(direction)
    {  
        case BAS:
            pos->y + rangeAttaque;
            break;
 
        case HAUT:
            pos->y - rangeAttaque;
            break;
 
        case DROITE:
            pos->x + rangeAttaque;
            break;
 
        case GAUCHE:
            pos->x - rangeAttaque;
            break;
 
        default:
            break;
    }
    
    SDL_RenderClear(render);
}

void botActions(int carte[][MAP_MAX_X], SDL_Rect *botTueur, SDL_Rect *joueur, SDL_Renderer *render)
{
    if (botTueur->x == joueur->x) //Joueur et bot sur la même horizontale
    {
        if(joueur->y > botTueur->y) //Joueur en dessous du bot
        {
            if(joueur->y - botTueur->y <= RANGE_BOT)
                attaque(carte, botTueur, BAS, render, RANGE_BOT);
            else
                mouvement(carte, botTueur, BAS, render);
        }
        else //Joueur au dessus du bot
        {
            if(botTueur->y - joueur->y <= RANGE_BOT)
                attaque(carte, botTueur, HAUT, render, RANGE_BOT);
            else
                mouvement(carte, botTueur, HAUT, render);
        }
    }
    else if (botTueur->y == joueur->y) //Joueur et bot sur la même verticale
    {
        if(joueur->x > botTueur->x) //Joueur à droite du bot
        {
            if(joueur->x - botTueur->x <= RANGE_BOT)
                attaque(carte, botTueur, DROITE, render, RANGE_BOT);
            else
                mouvement(carte, botTueur, DROITE, render);
        }
        else //Joueur à gauche du bot
        {
            if(botTueur->x - joueur->x <= RANGE_BOT)
                attaque(carte, botTueur, GAUCHE, render, RANGE_BOT);
            else
                mouvement(carte, botTueur, GAUCHE, render);
        }
    }
    else if(joueur->x > botTueur->x) //Joueur à droite du bot
    {
        if(joueur->y > botTueur->y) //Joueur en dessous du bot
        {
            if(joueur->y - botTueur->y > joueur->x - botTueur->x) //Joueur en dessous à droite du bot (proche en x)
                mouvement(carte, botTueur, BAS, render);
            else
                mouvement(carte, botTueur, DROITE, render);
        }
        else //Joueur au dessus du bot
        {
            if(botTueur->y - joueur->y > joueur->x - botTueur->x) //Joueur au dessus à droite du bot (proche en x)
                mouvement(carte, botTueur, HAUT, render);
            else
                mouvement(carte, botTueur, DROITE, render);
        }
    }
    else //Joueur à gauche du bot
    {
        if(joueur->y > botTueur->y) //Joueur en dessous du bot
        {
            if(joueur->y - botTueur->y > botTueur->x - joueur->x) //Joueur en dessous à gauche du bot (proche en x)
                mouvement(carte, botTueur, BAS, render);
            else
                mouvement(carte, botTueur, GAUCHE, render);
        }
        else //Joueur au dessus du bot
        {
            if(botTueur->y - joueur->y > joueur->x - botTueur->x) //Joueur au dessus à droite du bot (proche en x)
                mouvement(carte, botTueur, HAUT, render);
            else
                mouvement(carte, botTueur, GAUCHE, render);
        }
    }
}

int jouer(SDL_Renderer *render , SDL_Window *window)
{  

/**-------------------------Initialisation personnage-------------------------**/

    ///On crée des variables
    SDL_Rect position, positionJoueur, positionBot, positionB;

    SDL_Surface *sPerso[4] = {NULL};
    SDL_Texture *tPerso[4] = {NULL};

    SDL_Surface *sBot[4] = {NULL};
    SDL_Texture *tBot[4] = {NULL};

    SDL_Texture *persoActuelle = NULL;
    SDL_Texture *botTueur = NULL;

    ///Compteur_Variable
    int i;
    int cptBot, cptJoueur;
    cptBot = cptJoueur = 0;
    
    ///Definit les images sur les Surfaces Perso[Orientation]
    sPerso[0]=IMG_Load("images/stickman.bmp");
    sPerso[1]=IMG_Load("images/stickman.bmp");
    sPerso[2]=IMG_Load("images/stickman.bmp");
    sPerso[3]=IMG_Load("images/stickman.bmp");

    sBot[0] = IMG_Load("images/bot_de_la_mort_qui_tue.png");
    sBot[1] = IMG_Load("images/bot_de_la_mort_qui_tue.png");
    sBot[2] = IMG_Load("images/bot_de_la_mort_qui_tue.png");
    sBot[3] = IMG_Load("images/bot_de_la_mort_qui_tue.png");
 
    ///Définition de la carte
    int carte[MAP_MAX_Y][MAP_MAX_X];

    for(i = 0; i < 4; i++)
    {  
        if(sPerso[i] == NULL)
        {  
            SDL_ExitWithError("image personnage", window, render, NULL);
        }
        if(sBot[i] == NULL)
        {
            SDL_ExitWithError("image bot", window, render, NULL);
        }
    }

    for(i = 0; i < 4; i++)
    {
        tPerso[i] = SDL_CreateTextureFromSurface(render, sPerso[i]);
        SDL_FreeSurface(sPerso[i]);
        SDL_Log("Free surface perso %d", i);

        tBot[i] = SDL_CreateTextureFromSurface(render, sBot[i]);
        SDL_FreeSurface(sBot[i]);
        SDL_Log("Free surface bot %d", i);
    }

    ///On remet le render vierge
    SDL_RenderClear(render);
 
    ///Définission de la position du joueur et du bot
    persoActuelle = tPerso[BAS];
    if(persoActuelle == NULL)
        SDL_Log("Erreur persoActuelle");
    
    botTueur = tBot[BAS];
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

    ///Gestion des FPS
    unsigned int frameLimit = SDL_GetTicks() + 16;

/**-------------------------Programme principale du jeu-------------------------**/

    SDL_bool run = SDL_TRUE;
    SDL_Event event;

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
            }
            else if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_S])
            {
                mouvement(carte, &positionJoueur, GAUCHE, render);
                mouvement(carte, &positionJoueur, BAS, render);
            }
            else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_W])
            {
                mouvement(carte, &positionJoueur, DROITE, render);
                mouvement(carte, &positionJoueur, HAUT, render);
            }
            else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_S])
            {
                mouvement(carte, &positionJoueur, DROITE, render);
                mouvement(carte, &positionJoueur, BAS, render);
            }
            else if (keystate[SDL_SCANCODE_S])
                mouvement(carte, &positionJoueur, BAS, render);
            else if (keystate[SDL_SCANCODE_W])
                mouvement(carte, &positionJoueur, HAUT, render);
            else if (keystate[SDL_SCANCODE_D])
                mouvement(carte, &positionJoueur, DROITE, render);
            else if (keystate[SDL_SCANCODE_A])
                mouvement(carte, &positionJoueur, GAUCHE, render);
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
                            attaque(carte, &positionJoueur, HAUT, render, RANGE_JOUEUR);
                            break;
                        case SDLK_LEFT:
                            attaque(carte, &positionJoueur, GAUCHE, render, RANGE_JOUEUR);
                            break;
                        case SDLK_DOWN:
                            attaque(carte, &positionJoueur, BAS, render, RANGE_JOUEUR);
                            break;
                        case SDLK_RIGHT:
                            attaque(carte, &positionJoueur, DROITE, render, RANGE_JOUEUR);
                            break;

                        
                        default:
                            break;
                    }
 
                default:
                    break;
 
            }
        }

        if(cptBot == 6)
        {
            botActions(carte, &positionBot, &positionJoueur, render);
            cptBot = 0;
        }
        else 
            cptBot++;

        position.x = positionJoueur.x * TAILLE_BLOCK;
        position.y = positionJoueur.y * TAILLE_BLOCK;

        positionB.x = positionBot.x * TAILLE_BLOCK;
        positionB.y = positionBot.y * TAILLE_BLOCK;

        if(SDL_RenderCopy(render, persoActuelle, NULL, &position) != 0)
            SDL_Log("Erreur lors de l'affichage à l'écran");

        if(SDL_RenderCopy(render, botTueur, NULL, &positionB) != 0)
            SDL_Log("Erreur lors de l'affichage à l'écran");
 
        ///Gestion des 60 fps (1000ms/60 = 16.6 -> 16 
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;

        SDL_RenderPresent(render);
   		
    }
}
 
