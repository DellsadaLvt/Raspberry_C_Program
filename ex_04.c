#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>


// OUTPUT
#define red		12
#define green	18
#define	blue	16


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
	pinMode(	red , 	OUTPUT	);
	pinMode(	blue, 	OUTPUT	);
	pinMode(	green, 	OUTPUT	);
	pinMode(	button_00,	INPUT	);
	
	
	
	// INTERRUPTS
//wiringPiISR(	button_00, INT_EDGE_RISING, &handle_button_00	);

	
	
	
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
		digitalWrite( arrayLed[rand()%3] , 1);
		delay(1000);
		//int ran = rand()%3;
		//printf("rand %d\n", ran );
	}
}

