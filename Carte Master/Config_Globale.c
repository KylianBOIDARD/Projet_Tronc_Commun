//-----------------------------------------------------------------------------
// 				PROJET TRONC COMMUN 
//				FICHIER SOURCE CARTE MASTER
//-----------------------------------------------------------------------------
// AUTH: Equipe A4 -- CPE LYON -- 2021
// DATE: 24/02/2021
//-----------------------------------------------------------------------------
//				FICHIER CONFIGURATION GLOBALE
//
//-----------------------------------------------------------------------------
// Target: C8051F020
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include <C8051F020.h>
#include "c8051F020_SFR16.h"
void Init_Device(void) ;

//-----------------------------------------------------------------------------
// Dévalidation du watchdog
//-----------------------------------------------------------------------------
void Reset_Sources_Init()
{
	
	 WDTCN = 0xDE;
	 WDTCN = 0XAD;
	

}

//-----------------------------------------------------------------------------
// Config oscillateur - SYSCLK = 22,1184MHz - Oscillateur externe à quartz 
//-----------------------------------------------------------------------------
void Oscillator_Init_Quartz()
{

	  int i = 0;
    OSCXCN    = 0x67;  								// Config de l'horloge externe - Quartz > 6,7 MHz
    for (i = 0; i < 3000; i++);  			// attente stabilisation Fosc quartz
    while ((OSCXCN & 0x80) == 0); 		// validation stabilité du quartz
    OSCICN = 0x88;  									// Commutation sur oscillateur externe 
	        
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Configuration des Ports d'entrée-sorties
//-----------------------------------------------------------------------------

void Port_IO_Init()
{
	//------ FOM1 -----------------
		XBR2      |= 0x40;		//active crossbar
		XBR0      |= 0x04;		//active UART0
		P0MDOUT   |=  0x01;		//P0.1 en PP, TX0	
    // P0.0  -  RX0, Open-Drain, Digital
    // P0.1  -  TX0, Push-Pull, Digital
	//-------- FO_MS1 ---------------
		P0MDOUT |= (1<<2) ;		//P0.2 en PP, SCK
		P0MDOUT |= (1<<4) ;		//P0.4 en PP, MOSI
    // P0.2  -  SCK, Push-Pull, Digital
    // P0.3  -  MISO,  Open-Drain, Digital
    // P0.4  -  MOSI,  Push-Pull, Digital
    // P0.5  -  NSS,  Open-Drain, VDD
	//------ FOM2 -------------------
		XBR2 |= 0x44 ;			//uart1 enable
		P0MDOUT |= (1<<7) ;	//P0.7 en PP, TX1	
    // P0.6  -  RX1,  Open-Drain, Digital
    // P0.7  -  TX1,  Push-Pull, Digital
	//----- FOM3 ------------------- 
		P1MDOUT |= (1<<0) ;
    // P1.0  -  Servo Horizontal,  Push-Pull, Digital
//------ FOM4 --------------------
		P1MDOUT |= (1<<1) ;
		P1MDOUT |= (1<<2) ;
    // P1.1  -  TrigTelemetreAV,  Push-Pull, Digital
    // P1.2  -  TrigTelemetreAR,  Push-Pull, Digital
		// P3.6  -  ECHO_AV,  Open-Drain, Digital Input INT6
    // P3.7  -  ECHO_AR,  Open-Drain, Digital Input INT7
		
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  NSS_Slave,  Push-Pull, Digital
		// normalement pas besoin car 1 seul slave 
		
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    
		
		// P4.0 to P7.7   Unassigned,  Open-Drain, Digital
				

	 



//------- FOM3 ---------------
    P0MDOUT |= (1<<4); // set P0.4 output state to push-pull

//-------- FOM4 ----------------
		P2MDOUT |= 0x1F;
		

		
		
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//------- CONFIGURATION DE LA COMMUNICATION SPI ------------------------------------

void Config_SPI(void){
		SPIEN = 1 ;		//active la com SPI
		MSTEN = 1 ; 	//mode master 
		SPI0CKR = 4 ;	//réglage de SCK à SYSCLK/2*(4+1)= 2.21184 MHz
	
}

//----------------------------------------------------------------------------------
void Init_Device(void){
		Reset_Sources_Init();
		Oscillator_Init_Quartz();
    Port_IO_Init();
		EA = 1 ;											//enable all interrupts
		Config_SPI();
}









