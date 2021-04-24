/*======================= LIBRARIES =======================*/
#include<wiringPi.h>
#include<stdint.h>
#include<wiringPiI2C.h>
#include<stdio.h>
#include<math.h>

/*=======================  =======================*/


/*======================= DEFINE =======================*/
#define int_mpu 		7			// the pin int of mpu
#define Samp_rate		25			// 0x01: SMPLRT_DIV[7:0] is 1 ==> the sample rate: 500Hz
#define Config			26			// 0x02: FSYNC( input disable ), DLPF ( MODE 2)
#define Gyro_config 	27			// 0x08: no Self-test, full scale: 1 ==> +-500 do/sample
#define Acc_config		28			// 0x08: no self-test, full scale: 1 ==> +-4g, the sensity: 8192 LSB/g
#define Power_manager  	107			// 0x01: x axis gyroscope refer
#define Acc_x_out		59	
#define Acc_y_out		61
#define Acc_z_out		63
#define Ena_int 		56

/*======================= DECLARE FUNC =======================*/
void test_func( void);
void reset_all_register(const int *mpu);
void init_mpu(const int *mpu);
void read_register(const int *mpu, int reg);
void test_function(const int *mpu, const int8_t reg_add, int8_t value);
int16_t read_Acc(const int *mpu, uint8_t sensor_add);
float caculate_angle(const int *mpu, char mode[]);

/*======================= MAIN FUNCTION =======================*/
int main( void )
{
	/* INITIAL SETUP IO WITH WIRINGPI LIB */
	wiringPiSetupPhys();
	
	/* INITIAL I2C */
	int mpu = wiringPiI2CSetup(0x68);
	//printf("\nThe mpu value: %x\n", mpu);
	
	/* SETUP IO */
	pinMode( int_mpu, INPUT);
	
	/* RESET ALL REGISTER */
	//reset_all_register( &mpu );

	/*  INITIAL MPU*/
	init_mpu(&mpu);
	
	/*-------- WHILE LOOP ---------*/
	while(1)
	{
		float read = caculate_angle( &mpu, "pitch");
		//int16_t test = read_Acc( &mpu, Acc_x_out);
		printf("the read sensor: %f\n", read);
		delay(500); 	
	}
	
	return 0;
}


/*================ SUBROUTINE ==========================*/
void test_function( const int *mpu, const int8_t reg_add, int8_t value)
{
	wiringPiI2CWriteReg8( *mpu, reg_add	, value);
	printf("\nThe result: %x\n", wiringPiI2CReadReg8(*mpu, reg_add));
	
}
/*------------------------*/
void init_mpu(const int *mpu )
{
	wiringPiI2CWriteReg8(*mpu, Samp_rate, 1);
	wiringPiI2CWriteReg8(*mpu, Config, 2);
	wiringPiI2CWriteReg8(*mpu, Gyro_config, 0x08);
	wiringPiI2CWriteReg8(*mpu, Acc_config, 0x08);
	//wiringPiI2CWriteReg8(*mpu, Ena_int, 0x01);
	wiringPiI2CWriteReg8(*mpu, Power_manager, 0x01);
	
	printf("\nComplete config mpu\n"); 
}


/*------------------------*/
void reset_all_register( const int *mpu )
{
	wiringPiI2CWriteReg8(*mpu, Power_manager, 0x80); // should be transform 0x7F before 0x80 
														// if the result is not as expected
	read_register( &(*mpu), Power_manager);
	read_register( &(*mpu), Samp_rate);
}


/*------------------------*/
void read_register( const int *mpu,  int reg)
{
	printf("\nThe value of the reg[%d]: %x\n", reg, wiringPiI2CReadReg8(*mpu, reg));
}

/*------------------------*/
int16_t read_Acc( const int *mpu, uint8_t sensor_add)
{
			int16_t high	= wiringPiI2CReadReg8(*mpu, sensor_add);
			int16_t low		= wiringPiI2CReadReg8(*mpu, (sensor_add+1));
			int16_t Acc		= (high<<8) | low;
			return 	Acc;	
}

float caculate_angle( const int *mpu, char mode[] )
{
	float ax = (float)read_Acc(&(*mpu), Acc_x_out)/8192.0;
	float ay = (float)read_Acc(&(*mpu), Acc_y_out)/8192.0;
	float az = (float)read_Acc(&(*mpu), Acc_z_out)/8192.0;
	
	if( mode == "roll")
	{
		float roll= atan2(ay, sqrt(pow(ax,2) + pow(ay,2)))*180/M_PI;
		printf("roll\n");
		return roll;
	}
	else if( mode == "pitch")
	{
		float pitch= atan2(ax, sqrt( pow(az,2) + pow(ay,2)))*180/M_PI;
		printf("pitch\n");
		return pitch;
	}
	else
		printf("\nOut value\n");
	
}

