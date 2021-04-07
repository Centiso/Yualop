#ifndef _MAP_H_
#define _MAP_H_

#define MAP_MAX_Y 26
#define MAP_MAX_X 26

#define TILE_SIZE 32

#define CACHE_SIZE 5000
/*
typedef unsigned char tileindex;

typedef struct ss_tileProp
{
	SDL_Rect R;
	int mur;
	// tout ce que vous voulez...
} tileProp;

typedef struct s_map
{
	int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY; // nombre de tiles dans le tileset, en x et y
	SDL_Surface* tileset; // Un tableau de propriétés pour chaque tile
	tileProp* props;
	Uint16** schema;
	int nbtiles_largeur_monde,nbtiles_hauteur_monde; //Correspond a MAP_MAX_Y et MAP_MAX_X
} map;

SDL_Surface *load_surface(const char path[]);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
void ChargerMap_tileset(FILE* F,map* m,SDL_Renderer *renderer);
map* ChargerMap(const char* level, SDL_Renderer *renderer);
int AfficherMap(map* m,SDL_Surface* screen);
int LibererMap(map* m);

*/
#endif

