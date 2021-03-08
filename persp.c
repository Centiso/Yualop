/**
 * \file statiques.c
 * \brief Programme de je sais pas trop j'essaie de créer un personnage
 * \details Version avec pointeurs
 * \author Cécile SAIVET
 * \version 1.2
 * \date 16 février 2021
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

 typedef struct {
  char nom[20] ;
  int att;
  int def;
  int pdv;
 } t_pers ;


int *crea_pers (int faction, int level){
  t_pers *player;

player=malloc(sizeof(t_pers)*1);

if(faction==0){ // Est un gentil
  printf("Saisir votre pseudo : ");
  scanf("%s",&(player->nom)); printf("\n");
  player->pdv = 100;
  player->def = 50;
  player->att = 5;
  printf("Vous avez choisi le pseudo '%s' \n",player.nom);
  printf("Vous avez %d points de vie ", player.pdv);
  printf("%d points de defense (petit cadeau de depart) ", player.def);
  printf("et %d de force de frappe, il faut bien demarrer quelque part !\n \n", player.att);
}

if (faction ==1){ // Est un méchant
  player->pdv = 100;
  player->def = 25;
  player->att = 3;
}

void maj_lvl(int level, t_pers *player){

  if (faction ==0){
    for (int i = 0;i<level;i++){ //gentils

        pdv = pdv *0.1;
        def  = def * 0.1;
        att = att * 0.1;
    }
  }
  if (faction ==1){
    for (int i = 0;i<level;i++){ //mechants
        pdv = pdv *0.1;
        def  = def * 0.1;
        att = att * 0.1;
    }
  }
}

/*
  printf(" %s 🧙 ", player.nom);
  for (int coeur=0; coeur < ((player.pdv)/2); coeur++ ) {printf("🟦");}
  printf("\n"); printf(" %d🛡️ ", player.def); printf(" %d🗡️ \n", player.att);
*/
printf(" %s <(^-^)> ", player.nom);
for (int coeur=0; coeur < ((player.pdv)/2); coeur++ ) {printf("#");}
printf("\n"); printf(" %d [D]", player.def); printf(" %d o==[]::::::::> \n", player.att);

return (player);
}

int main (){
  t_pers * gentil;
  t_pers * mechant;

  gentil = crea_pers(0,1);

  mechant = crea_pers(1,1);
  printf( "test : nom gentil : %s, pdv mechant : %i \n", gentil->nom, mechant->pdv);

  free(gentil);
  free(mechant);
  gentil=NULL;
  mechant=NULL;

  return 0;
}
