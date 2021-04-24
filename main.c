#include<stdio.h>
#include<stdlib.h>   // uint16_t
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<math.h>	// gcc ... -lwiringPi -lm


#define sample_rate		25
#define config			26
#define gyro_config		27
#define acc_config		28
#define interrupts		56
#define	pwr_manager		107
#define acc_x			59
#define acc_y			61
#define acc_z			63


int mpu;
void init( void);
int16_t measure_acc(unsigned char add, unsigned char senser );

int main( void)
{
	
	/*SETUP I2C*/
	mpu = wiringPiI2CSetup(0x68);
	/*initial */
	init();
	
	while(1)
	{
	float ax = (float)measure_acc(mpu, acc_x)/4096.0;
	float ay = (float)measure_acc(mpu, acc_y)/4096.0;
	float az = (float)measure_acc(mpu, acc_z)/4096.0;
	
	float pitch = atan2(Ax, sqrt(pow(Ay,2)+pow(Az,2)))*180/M_PI;
	float roll = atan2(Ay, sqrt(pow(Ax,2)+pow(Az,2)))*180/M_PI;
	
	printf("ax p %f", pitch);
	delay(500);
	}
	return 0;
}


void init( void)
{
	/*25-> 28, 56, 107*/
	/*sample rate 500Hz*/
	wiringPiI2CWriteReg8(mpu,sample_rate,0x0e);
	/*khong su dung nguon xung ngoai, tat DLSP*/
	wiringPiI2CWriteReg8(mpu,config,0);
	/* gyro FS +- 500 o/s*/
	wiringPiI2CWriteReg8(mpu,gyro_config,0x08);
	/* acc FS: +-8g*/
	wiringPiI2CWriteReg8(mpu,acc_config,0x10);
	/* open interrupts of data readly */
	wiringPiI2CWriteReg8(mpu,interrupts,0x01);
	/* select the osc Gyro X */
	wiringPiI2CWriteReg8(mpu,pwr_manager,0x01);
}


int16_t measure_acc(unsigned char add, unsigned char senser )
{
	int16_t high, low, data;
	high = wiringPiI2CReadReg8(add, senser);
	low = wiringPiI2CReadReg8(add,senser );
	data = (high<<8) | low;
	return data;
}