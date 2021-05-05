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

// on re�oit de Master les infos suivantes :
//  -->allumage pointeur
//	-->pilotage pointeur servo
//	-->acquisition signaux
//	-->prise de vues
//on envoie � Master les donn�es de guidage si n�cessaire

void FF_MS1(char x){
		if( x == 1 ){//condition pour savoir si l'octet re�u correspond bien au 1er octet de d�but de trame
			SPI0DAT = 12 ; //octet de confirmation de reception, qui sera envoy� a master a la prochaine transmission
		}


}


void int_SPI(void) interrupt 6{
		SPIF = 0 ;			//remise a z�ro du flag de fin de transmission/reception du registre
		octet_recu = SPI0DAT ;	//lecture de l'octet re�u
		FF_MS1(octet_recu);
}











