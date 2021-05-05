/************** NOTE MCP4921 ********************/
// Voltage: 5V ( recoment: 3V3)
// Schematic
// SPI speed: 20MHz
// Data: 
// #bits: 16 bits
// MSB/LSB: MSB
// Register
/********************************/
/**** MAX7219 ****/
#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>
#include<wiringPiSPI.h>

#define spi_channel 0

unsigned char data[3]; // we only can send 8bits data in a time send
u_int16_t D; //
//unsigned short int D; 

int main( void )
{
	/* setup SPI */
	wiringPiSPISetup( spi_channel,10000000); 
	/* channel 0 or 1 speed 500KHz to 32MHz*/
	
	/* setup MCP4921 */
	data[0] = 0x30;// setup MSB in register of ic
	data[1] = 0;// LSB
	wiringPiSPIDataRW( spi_channel, data, 2);
	/* wiringPiDataRW( channel, buffer_store, size);
	/****************
	out( V ) = in ( D:  0 ==> 2^12)*  V_ref*(2^n -1)
	==> in_max = D;
	==> find D from V_outMax( 3.6V), V_ref = 5V
	==> want 100 times per circle so deltaD = D/100
	*****************/
	/* LOOP */
	while(1)
	{
		/* 100 values per cicle*/
		for(int i = 0; i< 100 ; i++)
		{
			D = 3.6*4095/5;
			D = D/i;
			data[0] = (D>>8) | 0x30;
			data[1] = D;
			wiringPiSPIDataRW( spi_channel, data, 2);
			delay(1);
		}
	}
	return 0;
}