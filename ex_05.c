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
volatile unsigned int arrayScore[12];


/********************** VARIABLES **********************/
//volatile unsigned int 
//unsigned int time;
unsigned int time_set, time;
volatile unsigned int time_press;
_Bool flag_mode, flag_annouce;
unsigned int soLan, avg;



/****************************** DECLARE FUNCTION *************************************/
void random_lighting ( void );
void interrupts_handle_button( char x );
void loop_time( void );
void blink( void );
void avg_func( void );



/********************** INTERRUPTS FUNCTION **********************/
void handle_button_00( void )
{
	 interrupts_handle_button( button_00);
}
/****************************/

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



	// INTERRUPTS
	wiringPiISR( button_00, INT_EDGE_RISING, &handle_button_00 );
	
	
	
	// INITIAL STATE
	time = 0;
	time_set = 1000;
	flag_mode = 0; 
	flag_annouce = 0;
	time_press = 0;
	soLan = 0;
	avg = 0;
	
	
	// 0 value is unenable press button
	/* turn off all led */
	for(int i=0; i<3; i++)
		digitalWrite(	arrayLed[i], 0	);
	
	for ( int i = 1; i < 11; i++)
	{
		arrayScore[i] = 0;
		//printf("pt %d\n", arrayScore[i]);	
	}
	
	for( int i = 0; i<2; i++)
	{
		digitalWrite(arrayLed[0], 1);
		delay(200);
		digitalWrite(arrayLed[0], 0);
		delay(100);
	}
	
	
	/********************* LOOP **************************/
	while( 1 )
	{
		loop_time();
	}
	
	
	return 0;
}


/********************* SUBROUTINE *****************/

/* USE RANDOM LIGHTING 10 TIMES */
void loop_time( void )
{
	while( soLan < 4)
	{
		random_lighting();
		soLan++;
		if( soLan >=4)
			avg_func();
		delay(2000);
	}
	
	
	
}


/* RANDOM LIGHTING */
void random_lighting ( void )
{	
	
	 /* LIGHTING RANDOM */
	if( (millis() - time) >= (time_set) )
	{
		//printf( "      time set is: %d \n" , time_set);
		digitalWrite(arrayLed[0], 1);
		time = millis();
		flag_annouce = 0;
		flag_mode = 1;											// 1 is enable press button 
		delay(1000);
		
		if( 0 == flag_annouce )
		{	
			flag_mode = 0;			// 0 is unenable press button
			digitalWrite(arrayLed[0], 0);
			printf( "goodluck later! \n ");
		}
		
		time_set = (rand()%5)*1000;
		//delay(3000);
		//printf("time set: %d \n" , time_set);
	} 
}



/* handle interrupts button */
/* x is the button, y is the position of led in array led */
void interrupts_handle_button( char x  )
{
	if( 1 == flag_mode )
		if( 1 == digitalRead( x ) )
		{
			delay(20);
			if( 1 == digitalRead( x ) )
			{
				flag_annouce = 1;
				flag_mode = 0;
				digitalWrite( arrayLed[0], 0);
				arrayScore[soLan] = millis() - time;
				printf( "time press [%d]: %d \n ", soLan,arrayScore[soLan]);
				
			}
		} 
}

/* blink func */
void blink (void)
{
		digitalWrite(arrayLed[0], 1);
		delay(200);
		digitalWrite(arrayLed[0], 0);
		delay(100);
}

/* average function */
void avg_func( void )
{
	float kq;
	int i;
	for(  i = 1; i< 3; i++)
	{
		arrayScore[i+1] = arrayScore[i+1] + arrayScore[i] ;
		kq = arrayScore[i+1];
		//printf("array[i]    : %d \n", arrayScore[i+1] );
	}
	kq = kq/3;
	printf("average: %0.6f \n", kq );
}