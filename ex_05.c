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
//unsigned int time;
unsigned int time_set, time, time_milli;
//_Bool 



/****************************** DECLARE FUNCTION *************************************/
void main_funtion ( void );



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
	time = 0;
	time_set = 1000;
	for(int i=0; i<3; i++)
		digitalWrite(	arrayLed[i], 0	);
	
	
	
	
	/********************* LOOP **************************/
	while( 1 )
	{
		main_funtion();
		
	}
	
	
	return 0;
}


/********************* SUBROUTINE *****************/
void main_funtion ( void )
{

	
		
	 /* LIGHTING RANDOM */
	if( (millis() - time) >= (time_set) )
	{
		time = millis();
		printf( "       time set is: %d \n" , time_set);
		digitalWrite(arrayLed[0], 1);
		delay(1000);
		digitalWrite(arrayLed[0], 0);
		time_set = (rand()%10)*1000;
		printf("time set: %d \n" , time_set);
		delay(500);
		
	} 
	
	
}