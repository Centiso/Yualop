#ifndef _MAP_H_
#define _MAP_H_

#define MAP_MAX_Y 26
#define MAP_MAX_X 26

#define TILE_SIZE 32

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

#endif