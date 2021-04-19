/**
 * \file test_persp.c
 * \brief Programme de test unitaire
 * \details Test unitaire sur les programmes de personnage
 * \author Cécile SAIVET
 * \version 1.0
 * \date 15 Mars 2021
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

#include "pers.h"

/**
* \fn t_pers *crea_pers (int faction, int level)
* \brief Création d'un personnage
* \details Fonction qui crée le personnage joueur et les ennemis
* \param faction Donne l'appartenance du personnage (gentil ou méchant)
* \param level Donne le pallier ou le personnage est rendu
* \return Retourne le personnage créée
*/
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


/**
* \fn void maj_lvl(int faction, t_pers *player)
* \brief Augmentation des statistiques
* \details Fonction qui met à jour les statistiques personnages par pallier
* \param faction donne l'appartemence du personnage
* \param *player donne le personnage à modifier
* \return Ne retourne rien il s'agit d'un void
*/
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

/**
* \fn int main (void)
* \brief Main du programme test personnage
* \details Permet de lancer le programme test du personnage
* \return return 0  
*/

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
