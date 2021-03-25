/**
 * \file persp.c
 * \brief Programme de création de personnage pluS le level up des stats
 * \details Version avec pointeurs regroupement de statiques.c et pers.c
 * \author Cécile SAIVET
 * \version 1.3
 * \date 08 Mars 2021
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
    player->lvl = 0;
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
  return (player);
}
/*
  printf(" %s 🧙 ", player.nom);
  for (int coeur=0; coeur < ((player.pdv)/2); coeur++ ) {printf("🟦");}
  printf("\n"); printf(" %d🛡️ ", player.def); printf(" %d🗡️ \n", player.att);
*/ /*
printf(" %s <(^-^)> ", player->nom);
for (int coeur=0; coeur < ((player->pdv)/2); coeur++ ) {printf("#");}
printf("\n"); printf(" %d [D]", player->def); printf(" %d o==[]::::::::> \n", player->att);

return (player);
}*/

//Fonction MAJ des stats par levels
void maj_lvl(int faction, t_pers *player){
int level = player->lvl;

  if (faction ==0){
    for (int i = 0;i<level;i++){ //gentils
//changer stats
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
