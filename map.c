#include "commun.h"
/*
SDL_Surface *load_surface(const char path[])
{
    SDL_Surface *tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
    return tmp;
}

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = load_surface(path); 
    SDL_Texture *texture = NULL;
    if(tmp)
    {
        texture = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_FreeSurface(tmp);
        if(NULL == texture)
            fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
    }
    return texture;
}

void ChargerMap_tileset(FILE* F,map* m, SDL_Renderer *renderer)
{
	int numtile,i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	char buf2[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #tileset
	m->tileset = load_surface(buf);
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

map* ChargerMap(const char* level, SDL_Renderer *renderer)
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
	ChargerMap_tileset(F,m,renderer);
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
}


*/