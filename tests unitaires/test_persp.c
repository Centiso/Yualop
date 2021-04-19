/**
 * \file test_persp.c
 * \brief Programme de test unitaire
 * \details Test unitaire sur les programmes de personnage
 * \author SAIVET Cécile
 * \version 1.0
 * \date Mars 2021
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

#include "pers.h"

 t_pers *crea_pers (int faction, int level){
    t_pers *player;

  player=malloc(sizeof(t_pers)*1);

  if(faction==0){ // Est un gentil
    printf("Saisir votre pseudo : ");
    scanf("%s",(player->nom)); printf("\n");
    player->pdv = 100;
    player->def = 50;
    player->att = 5;
    printf("Vous avez choisi le pseudo '%s' \n",player->nom);
    printf("Vous avez %d points de vie ", player->pdv);
    printf("%d points de defense (petit cadeau de depart) ", player->def);
    printf("et %d de force de frappe, il faut bien demarrer quelque part !\n \n", player->att);
  }

  if (faction ==1){ // Est un méchant
    player->pdv = 100;
    player->def = 25;
    player->att = 3;
  }
  return(player);
}

///Fonction MAJ des stats par levels
void maj_lvl(int faction, t_pers *player){
int level = player->lvl;

  if (faction ==0){
    for (int i = 0;i<level;i++){ //gentils

        player->pdv = player->pdv * 0.1;
        player->def  = player->def * 0.1;
        player->att = player->att * 0.1;
    }
  }
  if (faction ==1){
    for (int i = 0;i<level;i++){ //mechants
        player->pdv = player->pdv *0.1;
        player->def  = player->def * 0.1;
        player->att = player->att * 0.1;
    }
  }
}

int main (){
  t_pers * gentil;
  t_pers * mechant;

  gentil = crea_pers(0,1);

  mechant = crea_pers(1,1);
  printf( "test unitaire creation : nom gentil : %s, pdv mechant : %i \n", gentil->nom, mechant->pdv);

  free(gentil);
  free(mechant);
  gentil=NULL;
  mechant=NULL;

  return 0;
}
