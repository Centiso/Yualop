/**
 * \file test_u_stuffv2.h
 * \brief Test unitaire de stuffv2.c
 * \details C'est le main et les printf
 * \author Cécile SAIVET
 * \version 1.0
 * \date 17 Mars 2021
 */


 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<time.h>

 #include "pers.h"


int main (){
  t_objet *obj;
  srand(time(NULL));

  obj = crea_obj(0,CASQUE);
  printf("Test unitaire crea objet : CASQUE durabilite : %d, att : %d, def: %d \n", obj->durabilite, obj->att, obj->def);

  free(obj);
  obj=NULL;

  return 0;
}
