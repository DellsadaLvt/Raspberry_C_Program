#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>


/* declate the io pwm */
#define red		12   // 12 is the physical in rasp
#define blue	16
#define green	18



/* the function */
void sangDan(unsigned char x);
void tatDan(unsigned char x);
void ex_01();



int main(void)
{
	//setup lib
	wiringPiSetupPhys();
	

	
	//set io pwm	
	softPwmCreate( red, 0, 100);
	softPwmCreate( blue, 0, 100);
	softPwmCreate( green, 0, 100);

	
	// initial state
	digitalWrite( red, 0);
	digitalWrite( blue, 0);
	digitalWrite( green, 0);
	

	
	// loop 
	while( 1 )
	{
			
		ex_01();
		
	}
	
	
	
	
	
	return 0;
}

/********************** EX 01 *****************************/
void sangDan(unsigned char x)
{
	for( int i = 0; i < 11; i++)
	{
		softPwmWrite( x, i*10);
		delay(100);
	}
}


void tatDan(unsigned char x)
{

	for( int i = 10; i>=0; i--)
	{
		softPwmWrite(x, i*10);
		delay(100);
	}
}


void ex_01(void)
{
	sangDan(red);
	tatDan(red);
	sangDan(blue);
	tatDan(blue);
	sangDan(green);
	tatDan(green);
}



