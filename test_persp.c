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
 #include "persp.c"

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
