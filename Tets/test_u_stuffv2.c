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

 //#include "pers.h"
 #include "stuffv2.h"


 t_objet *crea_obj (int level, int cat){
     t_objet *item;

   item=malloc(sizeof(t_objet)*1);

   switch (cat){

 case OFF_HAND : item->durabilite=5;
                 item->att=0;
                 item->def=3;
                 break;
 case MAIN_HAND: item->durabilite=5;
                 item->att=2;
                 item->def=0;
                 break;
 case CASQUE:    item->durabilite=1000;
                 item->att=0;
                 item->def=15;
                 break;
 case PLASTRON:  item->durabilite=500;
                 item->att=0;
                 item->def=25;
                 break;
 case GANTS:     item->durabilite=100000;
                 item->att=0;
                 item->def=5;
                 break;
 case BOTTES:    item->durabilite=1000;
                 item->att=4;
                 item->def=5;
                 break;
 default : return 0;
 }

 return (item);
 }

 void maj_lvl_obj(int level, t_objet *obj){

     for (int i = 0;i<level;i++){ //gentils

         obj->durabilite = obj->durabilite * rand()%6;
         obj->att = obj->att * rand()%6;
     }
 }

int main (){
  t_objet *obj;
  srand(time(NULL));

  obj = crea_obj(0,CASQUE);
  printf("Test unitaire crea objet : CASQUE durabilite : %d, att : %d, def: %d \n", obj->durabilite, obj->att, obj->def);

  free(obj);
  obj=NULL;

  return 0;
}
