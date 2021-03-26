/********************** LIBRARIES **********************/
#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>


/*********************** INPUT **********************/
#define button_00	11				// use when red led high
#define button_01	13				// settup soLanSet
#define button_02	15				// reset all
#define button_03	7



/********************** OUTPUT **********************/
unsigned 	 		char arrayLed[4] = { 12, 18, 16 }; 	// 12 ==> red, 18 ==> green , 16 ==> blue
volatile unsigned 	int  arrayScore[12];					// store time when press button_00


/********************** VARIABLES **********************/
//volatile unsigned int 
//unsigned int time;
unsigned 			int			time_set, time;
volatile unsigned 	int 		time_press;
_Bool 							flag_mode, flag_annouce;
unsigned 			char 		soLan, soLanSet;



/******************** DECLARE FUNCTION ***************************/
void 	random_lighting( void );
void 	interrupts_handle_button( char x );
void 	loop_time( void );
void 	blink( void );
float	avg_func( char soPhanTu );
void 	reset_all( void );



/******************* INTERRUPTS FUNCTION ********************/
void handle_button_00( void )
{
	interrupts_handle_button( button_00);
}
/****************************/
void handle_button_02( void )
{
	if( soLan >= soLanSet )
		if( 1 == digitalRead( button_02 ) )
		{
			delay(20);
			if( 1 == digitalRead( button_02 ) )
			{
				for ( int i = 0; i < 12; i++)
					arrayScore[i] = 0;
				blink();
				delay(2000);
				soLan = 0;
			}
			
		}
}
/**********************/

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
	//led
	for(int i=0; i<3; i++)
		pinMode(	arrayLed[i], OUTPUT	);
	//button
		pinMode(	button_00,	INPUT	);



	// INTERRUPTS
	wiringPiISR( button_00, INT_EDGE_RISING, &handle_button_00 );
	//wiringPiISR( button_02, INT_EDGE_RISING, &handle_button_01 );
	wiringPiISR( button_02, INT_EDGE_RISING, &handle_button_02 );
	
	
	// reset all
	reset_all();
	
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
	while( soLan < soLanSet)
	{
		random_lighting();				
		delay(2000);
		soLan++;
		if( soLan >= soLanSet)	
			printf(" the result is: %0.2f \n", (avg_func(soLanSet)));
	}
}


/* RANDOM LIGHTING */
void random_lighting ( void )
{	
	 /* LIGHTING RANDOM */
	while( (millis() - time) < (time_set));
	
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
			printf("goodluck later!\n");
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
				printf("time press [%d]: %d\n", soLan,arrayScore[soLan]);
				
			}
		} 
}

/* blink func */
void blink (void)
{
	for(int i = 0; i<2 ; i++)
	{
		digitalWrite(arrayLed[0], 1);
		delay(200);
		digitalWrite(arrayLed[0], 0);
		delay(100);
	}
}

/* average function */
float avg_func( char soPhanTu )
{
	float result = 0;
	/* caculate sum of all components */
	for( char i = 0; i< (soPhanTu); i++)
		arrayScore[i+1] = arrayScore[i+1] + arrayScore[i] ;
	
	
	//printf("array[i]    : %d \n", arrayScore[i+1] );
	//printf("average: %0.6f \n", kq );
	result = (float)arrayScore[(soPhanTu)]/soPhanTu;
	
	return (result);
}



/* reset all func */
void reset_all( void )
{
	/* turn off all led */
	for(int i=0; i<3; i++)
		digitalWrite(	arrayLed[i], 0	);
	
	/* set all value in arrayScore is 0 */
	for ( int i = 0; i < 12; i++)
	{
		arrayScore[i] = 0;
		//printf("pt %d\n", arrayScore[i]);	
	}
	
	// INITIAL STATE
	time 			= 	0	;		// time = millis();
	time_set 		= 	1000;		// setup time lighting
	flag_mode 		= 	0	; 		// flag_mode: 0 :value is unenable press button
	flag_annouce 	= 	0	;		// flag_annouce: 0 : is unenable printf
	time_press		= 	0	;		// caculate time from led high to press butoon
	soLan 			= 	0	;		// the counter in while loop and the position in arrayScore
	soLanSet 		= 	3	;		// setup the time while loop
	
	
	blink();
	
	
	printf("RESET ALL\n");
	delay(1000);
}