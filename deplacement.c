#include "commun.h"




void mouvement(int Carte[][26], SDL_Rect *pos, int Direction, SDL_Renderer *render)
{
    SDL_Log("%d %d",pos->x,pos->y);
    switch(Direction)
    {  
        case BAS:
            if(pos->y + pos->h/TAILLE_BLOCK < HEIGHT/TAILLE_BLOCK)
                pos->y++;
            break;
 
        case HAUT:
            if(pos->y > 0)
                pos->y--;
             
            break;
 
        case DROITE:
            if(pos->x + pos->w/TAILLE_BLOCK < WIDTH/TAILLE_BLOCK)
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

void attaque(int Carte[][26], SDL_Rect *pos , int Direction, SDL_Renderer *render)
{
  
    switch(Direction)
    {  
        case BAS:
            
            pos->y + 2 ;

            break;
 
        case HAUT:
            
            pos->y-2;

            break;
 
        case DROITE:
            
            pos->x+2;

            break;
 
        case GAUCHE:
         
            pos->x-2;
             
            break;
 
        default:
            break;
    }
    
    SDL_RenderClear(render);
 
}

int jouer(SDL_Renderer *render , SDL_Window *window)
{  
 
    // On crée des variables
    SDL_Rect position, positionJoueur;
    SDL_Surface *sPerso[4] = {NULL};
    SDL_Texture *tPerso[4] = {NULL};
    SDL_Texture *persoActuelle = NULL;
 
    // Compteur_Variable
    int i;
    int j;
    
    // Definit les images sur les Surfaces Perso[Orientation]
    sPerso[0]=IMG_Load("images/stickman.bmp");
    sPerso[1]=IMG_Load("images/stickman.bmp");
    sPerso[2]=IMG_Load("images/stickman.bmp");
    sPerso[3]=IMG_Load("images/stickman.bmp");
 
    // Définition de la Carte
    int Carte[11][26];
 
    for(j = 0; j < 4; j++)
    {  
        if(sPerso[j] == NULL)
        {  
            printf("%d",j);
            printf("%d : Erreur SDL chargement de l'image Personnage \n",j );
            exit(EXIT_FAILURE);
        }
    }
 
    for(i = 0; i < 4; i++)
    {
        tPerso[i] = SDL_CreateTextureFromSurface(render, sPerso[i]);
        SDL_FreeSurface(sPerso[i]);
        SDL_Log("Free de la sufrace du perso %d", i);
    }
     
 
 
    // On remet le render vierge
    SDL_RenderClear(render);
 
    // On Définit la position du Joueur
    persoActuelle = tPerso[BAS];
    if(persoActuelle == NULL)
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    positionJoueur.x = 3;
    positionJoueur.y = 3;
    positionJoueur.w = 100;
    positionJoueur.h = 100;
    position.w = 100;
    position.h = 100;
 
/*-------------------------------------*/
/*------------ Boucle infini ----------*/
/*-------------------------------------*/
    SDL_bool run = SDL_TRUE;
    while(run)
    {  
        SDL_Event event;
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
                            printf("Le jeu est désormais en pause.\n");
							menu_pause(window, render);
                            break;
                        case SDLK_s:
                            mouvement(Carte, &positionJoueur, BAS, render);
                            break;
                        case SDLK_z:
                            mouvement(Carte, &positionJoueur, HAUT, render);
                            break;
                        case SDLK_d:
                            mouvement(Carte, &positionJoueur, DROITE, render);
                            break;
                        case SDLK_q:
                            mouvement(Carte, &positionJoueur, GAUCHE, render);
                            break;
                        case SDLK_UP:
                            attaque(Carte, &positionJoueur, HAUT, render);
                            break;
                        case SDLK_LEFT:
                            attaque(Carte, &positionJoueur, GAUCHE, render);
                            break;
                        case SDLK_DOWN:
                            attaque(Carte, &positionJoueur, BAS, render);
                            break;
                        case SDLK_RIGHT:
                            attaque(Carte, &positionJoueur, DROITE, render);
                            break;
                        default:
                            break;
                    }
 
                default:
                    break;
 
            }
        }

        position.x = positionJoueur.x * TAILLE_BLOCK;
        position.y = positionJoueur.y * TAILLE_BLOCK;

 
        if(SDL_RenderCopy(render, persoActuelle, NULL, &position) != 0)
            SDL_Log("Erreur lors de l'affichage à l'écran");
 
        SDL_RenderPresent(render);
 
    }
    SDL_DestroyRenderer(render);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
 
