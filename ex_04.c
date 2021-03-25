#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>


// INPUT
#define button_00	11
#define button_01	13
#define button_02	15
#define button_03	7



/* variables */
unsigned int arrayLed[4] = { 12, 18, 16 }; // 12 ==> red, 18 ==> green , 16 ==> blue
volatile unsigned int count;
unsigned int timez, led;
_Bool mode;



/****************************** DECLARE FUNCTION *************************************/
void controlLed( _Bool x);
void lighLedRandom( void );
/* x is the button, y is the position of led in array led */
void interrupts_handle_button( char x , char y );



// interrupts function
void handle_button_00( void )
{
	interrupts_handle_button(button_00, 0); 
}
/****************************/
void handle_button_01( void )
{
	interrupts_handle_button( button_01, 1);
}

/************************/
void handle_button_02( void )
{
	interrupts_handle_button( button_02, 2);
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
	timez	=	0;
	mode = 1;
	count = 0;
	for( int i=0; i<3; i++)
		digitalWrite( arrayLed[i], 0);
	
	
	/********************* LOOP **************************/
	while( 1 )
	{
		lighLedRandom();
		
	}
	
	
	return 0;
}


/********************* SUBROUTINE *****************/

void lighLedRandom( void )
{
	if(		millis() - timez >=	3000	)
	{
		timez = millis();
		
		// on led random
		led = rand()%3;
		digitalWrite( arrayLed[led] , 1);
		
		
		/* change mode */
		mode = 1; 									// true is allow press button
		
		
		/* print count */
		printf(" So lan nhan: %d \n", count);
		delay(500);
		
		// turn all led
		controlLed(0);
		
		
		/* unenable button */
		mode = 0; 									// false is not allow press button
	}
	
}

void controlLed( _Bool x)
{
	for( int i = 0; i< 3; i++  )
	{
		digitalWrite(arrayLed[i], x);
	}
}
/* x is the button, y is the position of led in array led */
void interrupts_handle_button( char x , char y )
{
	if( 1 == mode )
		if( y == led )
			if( 1 == digitalRead( x ) )
			{
				delay(20);
				if( 1 == digitalRead( x ) )
				{
					// create the time of press button
					count++;
					
					for( int j=0; j< 2; j++)
					{
						controlLed(1);
						delay(250);
						controlLed(0);
						delay(250);				
					}
					
				}
			} 
}


