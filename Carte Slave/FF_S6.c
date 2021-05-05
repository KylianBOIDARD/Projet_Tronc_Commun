//-----------------------------------------------------------------------------
// 				PROJET TRONC COMMUN 
//				FICHIER SOURCE CARTE SLAVE
//-----------------------------------------------------------------------------
// AUTH: Equipe A4 -- CPE LYON -- 2021
// DATE: 24/02/2021
//-----------------------------------------------------------------------------
//				FICHIER MAIN
//
//-----------------------------------------------------------------------------
// Target: C8051F020
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include "FF_SX.h"

char commande_recue = 0 ;

void FF_S6(void){
		if(commande_recue == 2){
				/*switch (ID de la commande){
        	case:
        		break;
        	case:
        		break;
        	default:
        		break;
        }*/
			
			
				commande_recue == 0 ;
		}
		
	
}

/*
void command_eclairage(void){
		FF_S1	
}*/


/*
void signaux_guidage(void){
		FF_S2
}*/



void command_servo_pointeur(void){
		char temps = 0 ;
	
		temps = FF_S3(90); //param Angle
}


/*
void command_photos(void){
		FF_S4
}*/


/*
void command_cortex(void){
		FF_S5
}*/

















