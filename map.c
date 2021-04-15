#include "commun.h"

void init_lab(int lab[N][M]){
//Initialise le labyrinthe avec des murs 
	int i,j;

	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			lab[i][j] = MUR;
}

//******************************
// Partie création du labyrinthe
//******************************

int valides(int i, int j){
// renvoie VRAI si i et j désignent une case de la matrice
	return(i>=0 && i<N &&j>=0 && j<M);
}

int est_vide(int i, int j, int lab[N][M]){
// renvoie VRAI si i et j désignent une case couloir
	return(valides(i,j) && lab[i][j]==COULOIR);
}

int est_mur(int i, int j, int lab[N][M]){
// renvoie VRAI si i et j désignent une case mur
	return(valides(i,j) && lab[i][j]==MUR);
}

int blocage(int i, int j, int lab[N][M]){
// renvoie VRAI si aucune case voisine n'est un mur
	return (!est_mur(i+2,j,lab) && !est_mur(i-2,j,lab)
		&& !est_mur(i,j+2,lab) && !est_mur(i,j-2,lab));
}

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

void initSalle(int lab[N][M], t_salle map[MAP_MAX_Y][MAP_MAX_X]){
	int i, j, l, k;
	
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(lab[i][j]==0){
				if(valides(i+1,j))
					map[i][j].porteBas = lab[i+1][j] == 0;

				if(valides(i-1,j))
					map[i][j].porteHaut = lab[i-1][j] == 0;

				if(valides(i,j+1) )
					map[i][j].porteDroite = lab[i][j+1] == 0;
				
				if(valides(i,j-1) )
					map[i][j].porteGauche = lab[i][j-1] == 0;

				for(l=0;l<N;i++){
					for(k=0;k<M;k++){
						
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
