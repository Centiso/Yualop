#include "commun.h"
<<<<<<< Updated upstream
#include <errno.h>

s_map map;
SDL_Renderer *renderer = NULL;

void loadMap(char *name);
void drawMap(int layer);
void cleanMaps(void);
void afficherTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);

void loadMap(char *name)
{
    int x, y;
    FILE *fp;
    errno_t err;
    //Ouvre le fichier en lecture (renvoie une erreur s'il n'existe pas)
    if (!(fp = fopen(name,"r"))){
        printf("Le fichier map n'a pas pu etre ouvert.\n");
        exit(1);
    }
    
    /* Lit les données du fichier dans la map */
     
    map.maxX = MAP_MAX_X;
    map.maxY = MAP_MAX_Y;
    
    
    for (y = 0; y < MAP_MAX_Y; y++){
        for (x = 0; x < MAP_MAX_X; x++){
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf(fp, "%d", &map.tile[y][x]);
        }
    }
    
    //Deuxième couche de tiles
    for (y = 0; y < MAP_MAX_Y; y++){
        for (x = 0; x < MAP_MAX_X; x++){
        fscanf(fp, "%d", &map.tile2[y][x]);
        }
    }
    
    /* on referme le fichier */
    fclose(fp);
    
}


void drawMap(int layer)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;
    
    mapX = map.startX / TILE_SIZE;
    
    /* Coordonnées de départ pour l'affichage de la map : permet
    de déterminer à quels coordonnées blitter la 1ère colonne de tiles au pixel près
    */
    x1 = (map.startX % TILE_SIZE) * -1;
    
    /* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
    Logiquement, on doit aller à x1 (départ) + WIDTH (la largeur de l'écran).
    Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
    va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
    blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
    if(x1 != 0)
    x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/
    x2 = x1 + WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    
    /* On fait exactement pareil pour calculer y */
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    
    /* Dessine la carte en commençant par startX et startY */
    
    /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
    de tile (qui fait 32 pixels de hauteur) */
    if (layer == 1) //Layer 1 = actions
    {
        for (y = y1; y < y2; y += TILE_SIZE){
            /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
            (0 au début puisqu'on ne scrolle pas) */
            mapX = map.startX / TILE_SIZE;
            
            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 à x = 640 */
            for (x = x1; x < x2; x += TILE_SIZE){
            
                /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tile[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;
                
                mapX++;
            }
    
        mapY++;
        }
    }
    
    else if (layer == 2){ //Layer 2 background
        //Deuxième couche de tiles
        for (y = y1; y < y2; y += TILE_SIZE){
            mapX = map.startX / TILE_SIZE;
            
            for (x = x1; x < x2; x += TILE_SIZE){
        
                /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tile2[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;
                
            }
        
            mapY++;
        }
    }
    
    
}


void cleanMaps(void)
{
    
    // Libère les textures des tilesets
    if (map.tileSet != NULL){
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }
    
    if (map.tileSetB != NULL){
        SDL_DestroyTexture(map.tileSetB);
        map.tileSetB = NULL;
    }
    
}


void afficherTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;
    
    /* Rectangle source */
    SDL_Rect src;
    
    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;
    
    /* Dessine la tile choisie sur l'écran aux coordonnées x et y */
    SDL_RenderCopy(renderer, image, &src, &dest);
=======

SDL_Renderer *renderer = NULL;

void ChargerMap_tileset(FILE* F,map* m)
{
	int numtile,i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	char buf2[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #tileset
	fscanf(F,"%s",buf); // nom du fichier
	m->tileset = IMG_Load(buf);
	fscanf(F,"%d %d",&m->nbtilesX,&m->nbtilesY);
	m->LARGEUR_TILE = m->tileset->w/m->nbtilesX;
	m->HAUTEUR_TILE = m->tileset->h/m->nbtilesY;
	m->props = malloc(m->nbtilesX*m->nbtilesY*sizeof(tileProp));
	for(j=0,numtile=0;j<m->nbtilesY;j++)
	{
		for(i=0;i<m->nbtilesX;i++,numtile++)
		{
			m->props[numtile].R.w = m->LARGEUR_TILE;
			m->props[numtile].R.h = m->HAUTEUR_TILE;
			m->props[numtile].R.x = i*m->LARGEUR_TILE;
			m->props[numtile].R.y = j*m->HAUTEUR_TILE;
			fscanf(F,"%s %s",buf,buf2);
			m->props[numtile].mur = 0;
			if (strcmp(buf2,"mur")==0)
				m->props[numtile].mur = 1;
		}
	}
}

map* ChargerMap(const char* level)
{
	FILE* F;
	map* m;
	F = fopen(level,"r");
	if (!F)
	{
		printf("fichier %s introuvable !! \n",level);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	m = malloc(sizeof(map));
	ChargerMap_tileset(F,m);
	fclose(F);
	return m;
}

int AfficherMap(map* m,SDL_Surface* screen)
{
	int i,j;
	SDL_Rect Rect_dest;
	int numero_tile;
	for(i=0;i<m->nbtiles_largeur_monde;i++)
	{
		for(j=0;j<m->nbtiles_hauteur_monde;j++)
		{
			Rect_dest.x = i*m->LARGEUR_TILE;
			Rect_dest.y = j*m->HAUTEUR_TILE;
			numero_tile = m->schema[i][j];
			SDL_BlitSurface(m->tileset,&(m->props[numero_tile].R),screen,&Rect_dest);
		}
	}
	return 0;
}

int LibererMap(map* m)
{
	int i;
	SDL_FreeSurface(m->tileset);
	for(i=0;i<m->nbtiles_hauteur_monde;i++)
		free(m->schema[i]);
	free(m->schema);
	free(m->props);
	free(m);
	return 0;
>>>>>>> Stashed changes
}


