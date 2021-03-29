/**
 * \file stuffv2.c
 * \brief Programme de stats stuff
 * \details Version avec pointeurs
 * \author Cécile SAIVET
 * \version 1.1
 * \date 17 Mars 2021
 */

 // Consigne : Faire struct t_equipement avec tête, bras, jambes etc... le rattacher à t_pers

 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<time.h>


#include "stuffv2.h"
//Protos + struct irons dans pers.h ou obj.h


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
