#include "commun.h"

void drop (int levelMonstre){
    
    int dropChance, aleaDrop , obj_cat, vieDrop, vie;
    obj_cat = rand()%7;
    dropChance = rand()%1000;
    vieDrop = rand()%20;
    aleaDrop = rand()%10;
    t_objet *item; 

        switch(dropChance){
            
            case 1 :
                switch (aleaDrop)
                {
                case 1:
                    switch (vieDrop)
                    {
                    case 1:
                        vie = 1;
                        break;
                    
                    default:
                        vie = 0.5;
                        break;
                    }
                    break;
                
                default:
                    item = crea_obj(levelMonstre, obj_cat);
                    maj_lvl_obj(levelMonstre, item);
                    break;
                }
                
                break;
            
            default :
                break;
        }


}