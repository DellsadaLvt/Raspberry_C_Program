/********************** LIBRARIES **********************/
#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>


/********************** INPUT **********************/
#define button_00	11
#define button_01	13
#define button_02	15
#define button_03	7



/********************** OUTPUT **********************/
unsigned int arrayLed[4] = { 12, 18, 16 }; // 12 ==> red, 18 ==> green , 16 ==> blue


/********************** VARIABLES **********************/
//volatile unsigned int 
//unsigned int 
//_Bool 



/****************************** DECLARE FUNCTION *************************************/
//
//



/********************** INTERRUPTS FUNCTION **********************/
void handle_button_00( void )
{
	 
}
/****************************/
void handle_button_01( void )
{
	
}

/************************/
void handle_button_02( void )
{
	
}
//
//
//
//
/****************************** MAIN FUNCTION *************************************/
int main( void )
{
	// SETUP LIB
	wiringPiSetupPhys();
	
	
	// SETUP IO
	for(int i=0; i<3; i++)
		pinMode(	arrayLed[i], OUTPUT	);
	pinMode(	button_00,	INPUT	);
	pinMode(	button_01,	INPUT	);
	pinMode(	button_02, 	INPUT	);
	pinMode(	button_03, 	INPUT	);

	
	
	
	// INTERRUPTS
	wiringPiISR( button_00, INT_EDGE_RISING, &handle_button_00 );
	wiringPiISR( button_01, INT_EDGE_RISING, &handle_button_01 );
	wiringPiISR( button_02, INT_EDGE_RISING, &handle_button_02 );
	
	
	// INITIAL STATE
	//
	//
	
	
	
	
	/********************* LOOP **************************/
	while( 1 )
	{
		
		
	}
	
	
	return 0;
}


/********************* SUBROUTINE *****************/
//
//