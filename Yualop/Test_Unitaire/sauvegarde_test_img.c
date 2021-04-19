#include "commun.h"

  // Initialize support for loading PNG and JPEG images
  /**
   * \fn SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
   * \brief Initialise une texture
   * \details Permet d'initialiser la texture d'un fichier
   * \param file_name le nom du fichier à texturer
   * \param *renderer le calque où il sera placé
   * \return Retourne l'image texturé
   */

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer)
{
	SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return image_texture;
}

/**
 * \fn void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
 * \brief Fonction d'erreur
 * \details Fonction qui test si tout fonctionne autrement il sort du programme pour erreur
 * \param *message Le message à tester
 * \param *w La fenêtre à tester
 * \param *r Le renderer à tester
 * \param *t La texture à tester
 * \return Ne retourne rien il s'agit d'un void
 */
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);

	if(strcmp(message, "IMG_Init"))
		IMG_Quit();
	if(TTF_WasInit())
		TTF_Quit();
	if(SDL_WasInit(SDL_INIT_VIDEO))
    	SDL_Quit();

    exit(EXIT_FAILURE);
}

/**
* \fn int main(int argc, char** argv)
* \brief Main du menu pause
* \details Affichage du menu pause lorsque le joueur est en jeu.
* \param argc
* \param ** argv
* \return Sors lors du succes
*/

int main(int argc, char** argv)
{
/**-------------------------Déclaration des variables principales-------------------------**/
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_bool program_launched = SDL_TRUE;

	const unsigned int FPS = 60;
	const unsigned int frameDelay = 1000 / FPS;

	unsigned long long frameStart;
	int frameTime;
t_stuff * playerStuff = malloc(sizeof(t_stuff)*1);
  t_objet *head;
  t_objet *chest=NULL;
  t_objet *gloves=NULL;
  t_objet *legs=NULL;
  t_objet *feet=NULL;
  t_objet *main_hand=NULL;
  t_objet *off_hand=NULL;
  t_objet *heart=NULL;
  t_objet *half_heart=NULL;
  playerStuff->head = head;
 	playerStuff->chest = chest; //pecs
  playerStuff->gloves = gloves;
 	playerStuff->legs= legs;
 	playerStuff->feet= feet;
 	playerStuff->main_hand= main_hand;
 	playerStuff->off_hand= off_hand;
  playerStuff->heart= heart;
  playerStuff->half_heart= half_heart;
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

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * image_texture = initialize_texture_from_file("../images/fond_noir.png", renderer);
    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = WIDTH;
    texture_destination.h = HEIGHT;
/**-------------------------Programme principal-------------------------**/

	while(program_launched)
	{
		//Clear screen
		SDL_RenderClear(renderer);

		//Draw
		SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

		//Show what was drawn
		SDL_RenderPresent(renderer);




//_______   PARTIE DE TEST SPECIFIQUE :  _________//
        		//création de ton rectangle
		SDL_Rect rect_pers_stuff;

		rect_pers_stuff.h = HEIGHT/2; //Hauteur image
		rect_pers_stuff.w = WIDTH/4; //Largeur image
		rect_pers_stuff.x = (WIDTH-rect_pers_stuff.w)-200; //Position du personnage en x (0 = gauche)
		rect_pers_stuff.y = HEIGHT/2 - (rect_pers_stuff.h / 2); //Position en y (0 = en haut)
/*
		//chargement de la texture (il te faut une varibale SDL_Texture *, une variable SDL_Surface * et SDL_Renderer *, initialisées à NULL)
		SDL_Texture * texture_stuff;
		texture_stuff = SDL_CreateTextureFromSurface(renderer, pers_stuff);

		//ensuite on nettoie la surface (vu qu'on a enregistré son contenue dans la texture on en a plus besoin pour le moment)
		SDL_FreeSurface(pers_stuff);
*/
//Initialisation nouvelle texture et Initialisation de la texture via l'image
		SDL_Texture * texture_stuff = initialize_texture_from_file("../images/perso.png", renderer);

		//ensuite on charge le rectangle (sinon l'image est l'image de base et ne peux pas décider où elle se trouvera sur le rendu, donc besoin de la variable renderer, texture et rect)
		SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_pers_stuff);

    //___________ITEMS STUFF____________________//
    SDL_Rect rect_item_stuff;

//________________Test pop stuff____________//
    if ( playerStuff->head != NULL ) {

     //____________________HEAD_____________________//
     	rect_item_stuff.h = HEIGHT/5; //Hauteur image
     	rect_item_stuff.w = WIDTH/7; //Largeur image
     	rect_item_stuff.x = rect_pers_stuff.x+60; //Position en x 0 = gauche
     	rect_item_stuff.y = rect_pers_stuff.y-70 ; //Position en y 0 = en haut 120 = mide

     	texture_stuff = initialize_texture_from_file("../images/stuff/head.png", renderer);
     	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

    }

//__________________Changer position entre chaque image__________________//
if ( playerStuff->head != NULL ) {
  //____________________HEAD_____________________//
  	rect_item_stuff.h = HEIGHT/5; //Hauteur image
  	rect_item_stuff.w = WIDTH/7; //Largeur image
  	rect_item_stuff.x = rect_pers_stuff.x+60; //Position en x 0 = gauche
  	rect_item_stuff.y = rect_pers_stuff.y-70 ; //Position en y 0 = en haut 120 = mide

  	texture_stuff = initialize_texture_from_file("../images/stuff/head.png", renderer);
  	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);


}

if ( playerStuff->legs != NULL ) {
  //____________________LEGS_____________________//
   rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
   rect_item_stuff.w = WIDTH/7; //Largeur image
   rect_item_stuff.x = rect_pers_stuff.x+80; //Position en x 0 = gauche
   rect_item_stuff.y = rect_pers_stuff.y+150 ; //Position en y 0 = en haut 120 = mide

   texture_stuff = initialize_texture_from_file("../images/stuff/legs.png", renderer);
   SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

}

if ( playerStuff->feet != NULL ) {

  //____________________FEET_____________________//
  	rect_item_stuff.h = HEIGHT/5; //Hauteur image
  	rect_item_stuff.w = WIDTH/7; //Largeur image
  	rect_item_stuff.x = rect_pers_stuff.x+87; //Position en x 0 = gauche
  	rect_item_stuff.y = rect_pers_stuff.y+222 ; //Position en y 0 = en haut 120 = mide

  	texture_stuff = initialize_texture_from_file("../images/stuff/feet.png", renderer);
  	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);
}


  if ( playerStuff->chest != NULL ) {
    //____________________CHEST_____________________//
    rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
    rect_item_stuff.w = WIDTH/7; //Largeur image
    rect_item_stuff.x = rect_pers_stuff.x+70; //Position en x 0 = gauche
    rect_item_stuff.y = rect_pers_stuff.y +80; //Position en y 0 = en haut 120 = mide

    /*
      SDL_FreeSurface(chest);  // Déjà présent dans la fonction d'initialisation
    */
       texture_stuff = initialize_texture_from_file("../images/stuff/chest.png", renderer);
       SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

  }
  if ( playerStuff->gloves != NULL ) {
//____________________GLOVES_____________________//
	rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
	rect_item_stuff.w = WIDTH/7; //Largeur image
	rect_item_stuff.x = rect_pers_stuff.x-60; //Position en x 0 = gauche
	rect_item_stuff.y = rect_pers_stuff.y+130 ; //Position en y 0 = en haut 120 = mide

	texture_stuff = initialize_texture_from_file("../images/stuff/gloves.png", renderer);
	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

}
  if ( playerStuff->main_hand != NULL ) {
//____________________MAIN_HAND_____________________//
	rect_item_stuff.h = HEIGHT/4; //Hauteur image
	rect_item_stuff.w = WIDTH/7; //Largeur image
	rect_item_stuff.x = rect_pers_stuff.x+255; //Position en x 0 = gauche
	rect_item_stuff.y = rect_pers_stuff.y+50 ; //Position en y 0 = en haut 120 = mide

	texture_stuff = initialize_texture_from_file("../images/stuff/main_hand.png", renderer);
	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);
}
  if ( playerStuff->off_hand != NULL ) {
//____________________OFF_HAND_____________________//
	rect_item_stuff.h = HEIGHT/4.5; //Hauteur image
	rect_item_stuff.w = WIDTH/7; //Largeur image
	rect_item_stuff.x = rect_pers_stuff.x-150; //Position en x 0 = gauche
	rect_item_stuff.y = rect_pers_stuff.y+100; //Position en y 0 = en haut 120 = mide

	texture_stuff = initialize_texture_from_file("../images/stuff/off_hand.png", renderer);
	SDL_RenderCopy(renderer, texture_stuff, NULL, &rect_item_stuff);

}
	//et enfin on affiche le rendu * Pas transferer dans le menu pause *
	SDL_RenderPresent(renderer);

//_______   FIN PARTIE DE TEST SPECIFIQUE  _________//
		SDL_Delay(10000);
		program_launched=0;

	}

/**-------------------------Libération de la mémoire allouée-------------------------**/

	SDL_DestroyTexture(image_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

/**-------------------------Fin du programme-------------------------**/

	return EXIT_SUCCESS;
}

