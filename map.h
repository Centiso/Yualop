#ifndef _MAP_H_
#define _MAP_H_

#define MAP_MAX_Y 26
#define MAP_MAX_X 26
#define CACHE_SIZE 5000
#define N 10
#define M 10
typedef struct s_salle{

	char tileset[MAP_MAX_Y][MAP_MAX_X];

	int porteHaut;
	int porteGauche;
	int porteDroite;
	int porteBas;

	int salleClear;

} t_salle;

void init_lab(int lab[N][M]);
int valides(int i, int j);
int est_vide(int i, int j, int lab[N][M]);
int est_mur(int i, int j, int lab[N][M]);
int blocage(int i, int j, int lab[N][M]);
int creer_lab(int lab[N][M]);
void initSalle(int lab[N][M], t_salle map[MAP_MAX_Y][MAP_MAX_X]);

#endif

