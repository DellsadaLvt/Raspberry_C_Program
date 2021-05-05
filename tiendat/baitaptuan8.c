#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <wiringPiI2C.h>
#include <math.h>



#define Sample_rate 	25
#define Config 			26
#define Gyro_config		27
#define Acc_config		28
#define Interrupt		56
#define PWR_Managment	107
#define Acc_X			59
#define Acc_Y			61
#define Acc_Z			63
#define INT				12


int mpu;
float t,tp,dt;
int16_t data;

int16_t read_sensor(unsigned char sensor)   
{
	// Đọc giá trị trên trục X
	int16_t high, low, data; // chứa các GT biến mức cao, thấp, GT ghép lại
	high = wiringPiI2CReadReg8(mpu, sensor);
	low = wiringPiI2CReadReg8(mpu,sensor +1);
	data = (high<<8) | low;
	return data;
}
void read_mpu(void)
{	
	float Ax=(float)read_sensor(Acc_X)/4096.0;
	float Ay=(float)read_sensor(Acc_Y)/4096.0;
	float Az=(float)read_sensor(Acc_Z)/4096.0;
	float picth= atan2(Ax,sqrt(pow(Ay,2)+pow(Az,2)))*180/M_PI;
	float roll = atan2(Ay,sqrt(pow(Ax,2)+pow(Az,2)))*180/M_PI;
	
	// xoa co ngat
	wiringPiI2CReadReg8(mpu,58);
}

void Init_6050(void)
{
	// sample rate 500Hz
	wiringPiI2CWriteReg8(mpu,Sample_rate,15);
	// khong su dung nguonn xung ngat ngoai, tat DLFP
	wiringPiI2CWriteReg8(mpu,Config,0);
	// Gyro FS: +-500 o/s
	wiringPiI2CWriteReg8(mpu,Gyro_config,0x08);
	// acc FS: +-8g
	wiringPiI2CWriteReg8(mpu,Acc_config,0x10);
	//mo interupt  cua data ready
	wiringPiI2CWriteReg8(mpu,Interrupt,1);
	// chon nguon xung Gyro X
	wiringPiI2CWriteReg8(mpu,PWR_Managment,0x01);

	
}
int main(void)
{

	// khai bao IO
	wiringPiSetupPhys();
	// setup giao tieo I2C
	mpu=wiringPiI2CSetup(0x68);
	// thiet lap che do do cho Mpu6050
	Init_6050();
	// khai bao ngat chan INT
	wiringPiISR(INT,INT_EDGE_RISING,&read_mpu);

	while(1)
	{
		
	}
	return 0;
	
	
}