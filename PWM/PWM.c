#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>



#define pwm0 		12
#define soft_Pwm 	11



int main(void)
{
	
	//Setup library wiringPi
	wiringPiSetupPhys();
	
	
	// setup IO
	pinMode(pwm0, PWM_OUTPUT);
	/* the default pwm is the baland
	/* led 50% */
	pwmWrite(pwm0,512);
	
	
	
	// set mode of pwm
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(15);
	pwmSetRange(128);  
	/*pwm freq = 19.2 Mhz / ( 15 * 128 )
	/* led 50% */
	pwmWrite(64);
	
	
	
	//soft pwm
	/* base freq = 100Hz*/
	/* duty cycle: 0 100 ( 10 ms ) */
	softPwmCreate( soft_Pwm, 0, 100);
	softPwmWrite( soft_Pwm, 70);
	

	while( 1 );


	
	return 0;
}