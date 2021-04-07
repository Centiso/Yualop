#ifndef _MAP_H_
#define _MAP_H_

#define MAP_MAX_Y 26
#define MAP_MAX_X 26

#define TILE_SIZE 32

<<<<<<< Updated upstream
typedef struct s_map
{
 
SDL_Texture *tileSet, *tileSetB;
 
//Numéro du tileset à utiliser
int tilesetAffiche;
 
/* Coordonnées de début, lorsqu'on doit dessiner la map */
int startX, startY;
 
/* Coordonnées max de fin de la map */
int maxX, maxY;
 
/* Tableau à double dimension représentant la map de tiles */
int tile[MAP_MAX_Y][MAP_MAX_X];
 
//Deuxième couche de tiles
int tile2[MAP_MAX_Y][MAP_MAX_X];
} s_map;


void initMaps(void);
void loadMap(char *name);
void drawMap(int layer);
void cleanMaps(void);
void afficherTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);

=======
#define CACHE_SIZE 5000

typedef struct ss_tileProp
{
	SDL_Rect R;
	int mur;
	// tout ce que vous voulez...
} tileProp;

typedef struct s_map
{
	int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY;
	SDL_Surface* tileset;
	tileProp* props;
	Uint16** schema;
	int nbtiles_largeur_monde,nbtiles_hauteur_monde;
} map;

void ChargerMap_tileset(FILE* F,map* m);
map* ChargerMap(const char* level);
int AfficherMap(map* m,SDL_Surface* screen);
int LibererMap(map* m);
>>>>>>> Stashed changes
#endif