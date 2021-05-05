//-----------------------------------------------------------------------------
// 				PROJET TRONC COMMUN 
//		FICHIER SOURCE COMMUNICATION MASTER <--> SLAVE
//-----------------------------------------------------------------------------
// AUTH: Equipe A4 -- CPE LYON -- 2021
// DATE: 24/02/2021
//-----------------------------------------------------------------------------
//				FICHIER SOURCE DU SOUS ENSEMBLE FF_MS1
//		
//-----------------------------------------------------------------------------
// Target: C8051F020
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include "FF_MS1.h"

extern commande_recue ;
char octet_recu = 0 ;

// on reçoit de Master les infos suivantes :
//  -->allumage pointeur
//	-->pilotage pointeur servo
//	-->acquisition signaux
//	-->prise de vues
//on envoie à Master les données de guidage si nécessaire

void FF_MS1(char x){
		if( x == 1 ){//condition pour savoir si l'octet reçu correspond bien au 1er octet de début de trame
			SPI0DAT = 12 ; //octet de confirmation de reception, qui sera envoyé a master a la prochaine transmission
		}


}


void int_SPI(void) interrupt 6{
		SPIF = 0 ;			//remise a zéro du flag de fin de transmission/reception du registre
		octet_recu = SPI0DAT ;	//lecture de l'octet reçu
		FF_MS1(octet_recu);
}











