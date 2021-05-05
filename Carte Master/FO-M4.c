//-----------------------------------------------------------------------------
// F0-M4.c //  Mesure distance – Télémètre Infrarouges ou télémètres Ultrasons
//-----------------------------------------------------------------------------
// AUTH: LAKKIS - DUCOURAU
// DATE: 17/03/2021
//
// Target: C8051F02x
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
// Utilisation du télémètre Ultrasons
#include "FO-M4.h"

sbit  TRIGGER_AV = P2^0; //Avant
sbit	ECHO1 		= P2^2;
sbit  TRIGGER_AR = P2^1; //Arrière
sbit	ECHO2 		= P2^3;
sbit	TIMER4 		= P2^4;


unsigned int   limit;
unsigned int   i_m4;
unsigned int  counter_ISR = 0;
unsigned int   last_counter = 0;
unsigned int   distance_AV;
unsigned int   distance_AR;
unsigned int   AR;
unsigned int   AV;
unsigned int distance;

void Init_FO_M4(void){
	//P2MDOUT |= 0x1F;	//fait dans la config globale
	
}

int FO_M4(char ordre){
	//Init_M4();
	if (ordre ==1){
		MES_Dist_AV();
	}
	if (ordre ==2){
		MES_Dist_AR();
	}
	return distance;
}

void MES_Dist_AV (void) {
	Trigger_AV();
	//On lance le Timer4 (mise a 1) mise a zero --> &=~
	AR = 0;
	AV = 1;
	EA=1;
	EIE2|=0x04;
	T4CON |= (0x04);
}

void MES_Dist_AR (void) {
	//Genere le trigger
	Trigger_AR();
	//On lance le Timer4 (mise a 1) mise a zero --> &=~
	AR = 1;
	AV = 0;
	T4CON |= (0x04);
}
	
	

/*Genere un signal carre de 10us a l'etat haut*/
void Trigger_AV (void) {
	TRIGGER_AV = 1;
	for (i_m4=0;i_m4<1;i_m4++) {
	}
	TRIGGER_AV = 0;
}
void Trigger_AR (void) {
	TRIGGER_AR = 1;
	for (i_m4=0;i_m4<1;i_m4++) {
	}
	TRIGGER_AR = 0;
}



/*Fonction appelee par le Time4 qui compte la duree d'impulsion a l'etat haut
	Stock dans last_counter la valeur du compteur (tick)*/
void Timer4_ISR (void) interrupt 16 {
	TIMER4=1;
	if (AR == 1) {
		//Si l'echo est a zero et que le compteur etait aussi a zero, on met quand meme a zero
		if (ECHO2 == 0 && counter_ISR == 0) {
			counter_ISR = 0;
		}
		//Si l'echo est nul et que le counter n'est pas nul, on vient d'avoir un front descendant, on stock la variable count_ISR
		//On lance la conversion et on desactive le timer4
		else if (ECHO2 == 0 && counter_ISR != 0) {
			last_counter = counter_ISR;
			counter_ISR = 0;
			T4CON |= ~(0x04);
			distance_AR = convert();
		}
		//Si l'echo est a 1 on increment le counter
		else {
			counter_ISR ++;
		}
	}
	
		if (AV == 1) {
		//Si l'echo est a zero et que le compteur etait aussi a zero, on met quand meme a zero
		if (ECHO1 == 0 && counter_ISR == 0) {
			counter_ISR = 0;
		}
		//Si l'echo est nul et que le counter n'est pas nul, on vient d'avoir un front descendant, on stock la variable count_ISR
		//On lance la conversion et on desactive le timer4
		if (ECHO1 == 0 && counter_ISR != 0) {
			last_counter = counter_ISR;
			counter_ISR = 0;
			T4CON &= ~(0x04);
			distance_AV = convert();
		}
		//Si l'echo est a 1 on increment le counter
		if (ECHO1 == 1) {
			counter_ISR ++;
		}
	}
	//Clear flag timer4 
	TIMER4=0;
	T4CON &= ~(0x80);
}





/* Converti le nombre de ticks (last_counter) en distance en cm*/
unsigned int convert (void) {
	last_counter = (last_counter - 1);
	//Formule : distance (cm) = time(us)/58
	//On a une interruption toutes les 30us
	distance =(last_counter * 30)/58;
	return distance;
}
