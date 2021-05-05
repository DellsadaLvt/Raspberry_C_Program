#include <stdio.h>
#include <wiringPi.h>

#define red		12   // 12 is the physical in rasp
#define blue	16
#define green	18


#define button_00		11
#define button_01		13
#define button_02		15
#define button_03		7


		

// func interrupts
	void handle_interrupts(void)
	{
		if(	1 == digitalRead(button_00) )
		{
				digitalWrite(	red , 1	);
				printf(" led red is on \n");
		}

	}
	
	void handle_button_03( void )
	{
		if( 1 == digitalRead( button_03 ) )
		{
			printf( "led red is off \n");
			digitalWrite(	red, 0	);
		}
	}

int main(void)
{
	//setup library
	wiringPiSetupPhys();
	
	// declarate IO
	pinMode(	red , 	OUTPUT	);
	pinMode(	blue, 	OUTPUT	);
	pinMode(	green, 	OUTPUT	);
	pinMode(	button_00,	INPUT	);
	pinMode(	button_01,	INPUT	);
	pinMode(	button_02, 	INPUT	);
	pinMode(	button_03, 	INPUT	);
	
	// interrupts
	wiringPiISR(	button_00 ,  INT_EDGE_RISING, &handle_interrupts	);
	wiringPiISR(	button_03 ,  INT_EDGE_RISING, &handle_button_03		);
	
	// initial state
	digitalWrite(	red, 	0	);
	digitalWrite(	blue, 	0	);
	digitalWrite(	green, 	0	);
	
	
	
	//r
	while(1)
	{
		
		
	}
	
	
	return 0;
}