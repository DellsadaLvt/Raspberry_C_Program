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
#define button_01	13
#define button_02	15
#define button_03	7


/* variables */
short signed int mode, light;
unsigned int arrayLed[4] = { 12, 18, 16 };
unsigned int timez;


// function declare
void lighLedRandom( void );



/* INTERRUPTS FUNC */
void handle_button_00( void )
{
	/* if( 1 == digitalRead(button_00) )
	{
		delay(10);
		if( 1 == digitalRead(button_00) )
		{
			mode++;
			if( 2 < mode )
				mode = 0;
			printf("Mode: %d \n", mode);
			printf("Light level: %d \n", light);
		}
	} */
}
/*******************/
void handle_button_01( void )
{
	
}
/*****************************/
void handle_button_02( void )
{
	
}
/**************************************/
void handle_button_03( void )
{
	
	
}
	



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
	pinMode(	button_01,	INPUT	);
	pinMode(	button_02, 	INPUT	);
	pinMode(	button_03, 	INPUT	);
	
	
	// INTERRUPTS
	wiringPiISR(	button_00, INT_EDGE_RISING, &handle_button_00	);
	wiringPiISR(	button_01, INT_EDGE_RISING, &handle_button_01	);
	wiringPiISR(	button_02, INT_EDGE_RISING, &handle_button_02	);
	wiringPiISR(	button_03, INT_EDGE_RISING, &handle_button_03	);
	
	
	// SETUP SOFTPWM
	softPwmCreate(	red, 	0, 100	);
	softPwmCreate(	blue,	0, 100	);
	softPwmCreate(	green,	0, 100	);
	
	
	// INITIAL STATE
	mode	= 	0;
	light	=	0;
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

