#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>


// INPUT
#define button_00	11



/* variables */
unsigned int arrayLed[4] = { 12, 18, 16 };
unsigned int timez;


// function declare
void lighLedRandom( void );




// MAIN FUNCTION
int main( void )
{
	// SETUP LIB
	wiringPiSetupPhys();
	
	
	// SETUP IO
	pinMode(	red , 		OUTPUT	);
	pinMode(	blue, 		OUTPUT	);
	pinMode(	green, 		OUTPUT	);
	pinMode(	button_00,	INPUT	);
	
	
	// INITIAL STATE
	timez	=	0;
	
	
	// LOOP 
	while( 1 )
	{
		lighLedRandom();
	}
	
	
	return 0;
}


/********************* subroutine *****************/

void lighLedRandom( void )
{
	if( millis() - timez >=	3000	)
	{
		timez = millis();
		
		// on led random
		digitalWrite( arrayLed[rand()%3] , 1);
		
		delay(500);
		
		// turn all led
		digitalWrite( red,	0);
		digitalWrite( blue,  0);
		digitalWrite( green, 0);

	}
}

