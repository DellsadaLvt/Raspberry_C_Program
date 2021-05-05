#include<stdio.h>
#include<stdint.h>
#include<wiringPi.h>

int main( void)
{
	int8_t a = 0x12;
	int8_t b = 0x56;
	int16_t c = b;
	c = (b<<8) | a;
	
	printf(" the result is: %x\n", c);
}