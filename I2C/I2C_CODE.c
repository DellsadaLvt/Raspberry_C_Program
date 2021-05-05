/*
detect address of slave:
	i2cdetect -y 1    where 1 is the first slave
	gpio i2cdetect
*/
#include<wiringPi.h>
#include<wiringPiI2C.h>


int main( void )
{
	/*setup 	I2C*/
	//declare address's rt
	int rt = wiringPiI2CSetup(0x60);
	//declare address's mcu
	int mpu = wiringPiI2CSetup(0x68);
	
	
	unsigned char data;
	data = 0x06;
	// wiringPiI2CWriteReg8(address, register, data);
	wiringPiI2CWriteReg8(rt, 0x01, data);
	
	return 0;
}

