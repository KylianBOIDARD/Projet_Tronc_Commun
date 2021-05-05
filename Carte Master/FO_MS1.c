//-----------------------------------------------------------------------------
// 				PROJET TRONC COMMUN 
//		FICHIER SOURCE COMMUNICATION MASTER <--> SLAVE
//-----------------------------------------------------------------------------
// AUTH: Equipe A4 -- CPE LYON -- 2021
// DATE: 24/02/2021
//-----------------------------------------------------------------------------
//				FICHIER SOURCE DU SOUS ENSEMBLE FO_MS1
//		
//-----------------------------------------------------------------------------
// Target: C8051F020
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include "FO-MX.h"

sbit NSS_Slave = P2^0 ;		//port pour selectionner le slave avec qui communiquer

extern COMMANDES commande ;
char var_to_transmit = 0 ;
char transmission_en_cours = 1 ;
// il faut envoyer des variables de COMMANDES à la carte Slave
//  -->allumage pointeur
//	-->pilotage pointeur servo
//	-->acquisition signaux
//	-->prise de vues
//on reçoit en retour les données de guidage si demandées

//		TAILES DES VARIABLES :
// char ou uchar : 1 octet
// int : 2 octets 

void send_slave(int x){
		
		if (x == 0){		//demande mouvement servo V
				
		}
		if (x == 1){		//demande allumage pointeur
			NSS_Slave = 0 ;		//on selectionne l'esclave
			
			//SPI0DAT = ?? ;		//doubles octets
			//SPI0DAT = ?? ;		//de debut de trame
			
			SPI0DAT = commande.Etat_Lumiere ;		//on démarre la com
			while(transmission_en_cours == 1){}	//on attend 
			transmission_en_cours = 1 ;
				
			SPI0DAT = commande.Lumiere_Intensite ;
			while(transmission_en_cours == 1){}
			transmission_en_cours = 1 ;
			
			SPI0DAT = commande.Lumiere_Duree ;
			while(transmission_en_cours == 1){}
			transmission_en_cours = 1 ;
				
			SPI0DAT = commande.Lumiere_Extinction ;
			while(transmission_en_cours == 1){}
			transmission_en_cours = 1 ;
			
			SPI0DAT = commande.Lumiere_Nbre ;
			while(transmission_en_cours == 1){}
			transmission_en_cours = 1 ;
			
			//SPI0DAT = ?? ;		//doubles octets
			//SPI0DAT = ?? ;		//de fin de trame
		}
		if (x == 2){		//demande prise de photos
				
		}



}


void int_SPI(void) interrupt 6{
		SPIF = 0 ;			//remise a zéro du flag de fin de transmission/reception du registre
		transmission_en_cours = 0 ;			//on indique que le bit a été transmis
		//on doit lire le retour de Slave si necessaire
		//recup_slave()??
}






