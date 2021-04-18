#include "commun.h"

/**
 * \file jeu.c
 * \brief Contient la création du labyrinthe et la création des salles de jeu
 * \author TACHET Nicolas
 * \version 1.0
 * \date Avril 2021
 */


/**
 * \fn init_lab(int lab[N][M])
 * \brief Initialise le labyrinthe avec des murs 
 */
void init_lab(int lab[N][M]){
	int i,j;

	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			lab[i][j] = MUR;
}


// Partie création du labyrinthe

/**
 * \fn valides(int i, int j)
 * \brief renvoie VRAI si i et j désignent une case de la matrice
 */
int valides(int i, int j){
	return(i>=0 && i<N &&j>=0 && j<M);
}

/**
 * \fn est_vide(int i, int j, int lab[N][M])
 * \brief renvoie VRAI si i et j désignent une case couloir
 */
int est_vide(int i, int j, int lab[N][M]){
	return(valides(i,j) && lab[i][j]==COULOIR);
}

/**
 * \fn est_mur(int i, int j, int lab[N][M])
 * \brief renvoie VRAI si i et j désignent une case mur
 */
int est_mur(int i, int j, int lab[N][M]){

	return(valides(i,j) && lab[i][j]==MUR);
}
/**
 * \fn blocage(int i, int j, int lab[N][M])
 * \brief renvoie VRAI si aucune case voisine n'est un mur
 */

int blocage(int i, int j, int lab[N][M]){
	return (!est_mur(i+2,j,lab) && !est_mur(i-2,j,lab)
		&& !est_mur(i,j+2,lab) && !est_mur(i,j-2,lab));
}
/**
 * \fn creer_lab(int lab[N][M])
 * \brief crée le labyrinthe parfait de la partie de jeu.
 */
int creer_lab(int lab[N][M]){

	int termine=FAUX;
	int trouve=FAUX;
	int i,j,alea;
	init_lab(lab);
	i=0,j=0;
	Pile *maPile = initialiser();

	lab[0][0]=COULOIR;
	   while(!termine){

	if(blocage(i,j,lab)){
		if(maPile==NULL){
			depiler(maPile);
			depiler(maPile);
		}
		else
			termine=VRAI;
	}
	else{
		trouve=FAUX;
		while(!trouve){
			alea=rand()%4; 
			switch(alea){
				case 0: 
					if(est_mur(i+2,j,lab)){ 
						empiler(maPile,i);
						empiler(maPile,j);
						lab[i+1][j]=COULOIR;
						lab[i+2][j]=COULOIR;
						i=i+2;
						trouve=VRAI;
						break;
					}	
				case 1: 	
					if(est_mur(i-2,j,lab)){
						empiler(maPile,i);
						empiler(maPile,j);
						lab[i-1][j]=COULOIR;
						lab[i-2][j]=COULOIR;
						i=i-2;
						trouve=VRAI;
						break;
					}	
				case 2: 	
					if(est_mur(i,j+2,lab)){
						empiler(maPile,i);
						empiler(maPile,j);
						lab[i][j+1]=COULOIR;
						lab[i][j+2]=COULOIR;
						j=j+2;
						trouve=VRAI;
						break;
					}	
				case 3: 	
					if(est_mur(i,j-2,lab)){
						empiler(maPile,i);
						empiler(maPile,j);
						lab[i][j-1]=COULOIR;
						lab[i][j-2]=COULOIR;
						j=j-2;
						trouve=VRAI;
					}	
			}
		}
	}
   }
}

/**
 * \fn initSalle(int lab[N][M], t_salle map[MAP_MAX_Y][MAP_MAX_X])
 * \brief génère les salles de jeu
 */
void initSalle(int lab[N][M], t_salle map[MAP_MAX_Y][MAP_MAX_X]){
	int i, j, l, k;
	printf("1");
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(lab[i][j]==0){
				if(valides(i+1,j))
					map[i][j].porteBas = lab[i+1][j] == 0;
					printf("1");

				if(valides(i-1,j))
					map[i][j].porteHaut = lab[i-1][j] == 0;
					printf("2");
				if(valides(i,j+1) )
					map[i][j].porteDroite = lab[i][j+1] == 0;
					printf("3");
				if(valides(i,j-1) )
					map[i][j].porteGauche = lab[i][j-1] == 0;
					printf("4");
				for(l=0;l<N;i++){
					for(k=0;k<M;k++){
						printf("5");
						if(l == 0 || k == 0 || l == 25 || k == 25)
							map[i][j].tileset[l][k] = '2';
						
						else
							map[i][j].tileset[l][k] = '0';

						if(map[i][j].porteBas){
							map[i][j].tileset[25][12] = '1';
							map[i][j].tileset[25][13] = '1';
						}

						if(map[i][j].porteHaut){
							map[i][j].tileset[0][12] = '1';
							map[i][j].tileset[0][13] = '1';
						}

						if(map[i][j].porteGauche){
							map[i][j].tileset[12][0] = '1';
							map[i][j].tileset[13][0] = '1';
						}

						if(map[i][j].porteDroite){
							map[i][j].tileset[12][25] = '1';
							map[i][j].tileset[13][25] = '1';
						}
					}
				}
				
			}	
		}
	}
}
