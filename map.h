#ifndef _MAP_H_
#define _MAP_H_

#define MAP_MAX_Y 26
#define MAP_MAX_X 26

typedef struct s_map
{
    SDL_Surface *background, *tileSet;

    //Coordonnées de début, lorsqu'on doit dessiner la map
    int startX, startY;

    //Coordonnées max de fin de la map
    int maxX, maxY;

    //Complession du niveau
    int levelClear;

    //Tableau à double dimension représentant la map de tiles
    int tile[MAP_MAX_Y][MAP_MAX_X];

} t_map;

#endif