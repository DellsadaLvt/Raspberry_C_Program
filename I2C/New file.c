#include<wiringPi.h>
#include<wiringPiI2C.h>

// DS3231, MPU 6050, MAX7219, MCP4921

int main ( void )
{
	/*SETUP I2C*/
	int ds3231 = wiringPiI2CSetup(0x68);
	
	/* SETUP HOUR IN AM/PM MODE */
	int hh, mm, ss;
	hh = 0x62;
	mm = 0x49;
	ss = 0x26;
	
	wiringPiI2CWriteReg8(ds3231, 0x00, ss);
	wiringPiI2CWriteReg8(ds3231, 0x01, mm);
	wiringPiI2CWriteReg8(ds3231, 0x02, hh);
	
	return 0;
}