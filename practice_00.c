/*======================= LIBRARIES =======================*/
#include<wiringPi.h>
#include<stdint.h>
#include<wiringPiI2C.h>
#include<stdio.h>
/*=======================  =======================*/


/*======================= DEFINE =======================*/
#define int_mpu 		7			// the pin int of mpu
#define Samp_rate		25			// 0x01: SMPLRT_DIV[7:0] is 1 ==> the sample rate: 500Hz
#define Config			26			// 0x02: FSYNC( input disable ), DLPF ( MODE 2)
#define Gyro_config 	27			// 0x08: no Self-test, full scale: 1 ==> +-500 do/sample
#define Acc_config		28			// 0x08: no self-test, full scale: 1 ==> +-4g
#define Power_manager  	107			//

/*======================= DECLARE FUNC =======================*/
void test_func( void);
void reset_all_register( int mpu );
void init_mpu( int mpu );
void read_register(  int mpu, int reg);


/*======================= MAIN FUNCTION =======================*/
int main( void )
{
	/* INITIAL SETUP IO WITH WIRINGPI LIB */
	wiringPiSetupPhys();
	
	/* INITIAL I2C */
	int mpu = wiringPiI2CSetup(0x68);
	printf("\nThe mpu value: %x\n", mpu);
	
	/* SETUP IO */
	pinMode( int_mpu, INPUT)	;
	
	/* RESET ALL REGISTER */
	reset_all_register( mpu );
	
	/*  INITIAL MPU*/
	
	
	
	
	return 0;
}


/*================ SUBROUTINE ==========================*/
void test_func( void)
{
	
}
/*------------------------*/
void init_mpu( int mpu )
{
	wiringPiI2CWriteReg8(mpu, Samp_rate, 0x01);
	wiringPiI2CWriteReg8(mpu, Config, 0x02);
	wiringPiI2CWriteReg8(mpu, Gyro_config, 0x08);
	wiringPiI2CWriteReg8(mpu, Acc_config, 0x08);
	wiringPiI2CWriteReg8(mpu, Power_manager, 0x01);
}


/*------------------------*/
void reset_all_register( int mpu )
{
	wiringPiI2CWriteReg8(mpu, Power_manager, 0x80);
	read_register(mpu, Power_manager);
	read_register(mpu, Samp_rate);
}


/*------------------------*/
void read_register( int mpu,  int reg)
{
	printf("\nThe value of the reg[%d]: %x\n", reg, wiringPiI2CReadReg8(mpu, reg));
}

