// Cảm biến gia tốc MPU - 6050
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h> // Định dạng số nguyên mới code C (int16_t)
#include <math.h> // Sử dụng hàm art, sin, cos,...
	// gcc ... -lwiringPi -lm
#define Sample_rate			25 // 0x19
#define Config				26
#define	Gyro_config			27 
#define	Acc_config			28
#define Interrupt			56
#define PWR_Management		107
#define Acc_X				59
#define Acc_Y				61
#define Acc_Z				63

#define INT 11
float t,tp,dt;
int mpu;
//int16_t data;

int16_t read_sensor(unsigned char sensor)   
{
	// Đọc giá trị trên trục X
	int16_t high, low, data; // chứa các GT biến mức cao, thấp, GT ghép lại
	high = wiringPiI2CReadReg8(mpu, sensor);
	low = wiringPiI2CReadReg8(mpu,sensor +1);
	data = (high<<8) | low;
	return data;
}

void Init_6050(void)
{
	// register 25->>28,56,107
	// sample_rate 500Hz : 2ms/mẫu
	wiringPiI2CWriteReg8(mpu, Sample_rate, 1);
	
	// Không sử dụng nguồn xung ngoài, tắt bộ lọc số DLFP
	wiringPiI2CWriteReg8(mpu, Config, 2);
	
	// Gyro FS : +- 500 độ/s
	wiringPiI2CWriteReg8(mpu, Gyro_config, 0x08);
	
	// acc FS : +- 8g
	wiringPiI2CWriteReg8(mpu, Acc_config, 0x08);
	
	// mở Interrupt của data ready, khi đo xong 1 mẫu sẽ 
	// làm thay đồi trạng thái chân int mpu 6050
	wiringPiI2CWriteReg8(mpu, Interrupt, 1);
	
	// chọn nguồn xung Gyro X
	wiringPiI2CWriteReg8(mpu, PWR_Management, 0x01);
	
}
	
void read_mpu(void)
{
	//t=millis();
	//dt=t-tp;
	float Ax = (float)read_sensor(Acc_X)/8192.0;
	float Ay = (float)read_sensor(Acc_Y)/8192.0;
	float Az = (float)read_sensor(Acc_Z)/8192.0;
	float pitch = atan2(Ax, sqrt(pow(Ay,2)+pow(Az,2)))*180/M_PI;
	float roll = atan2(Ay, sqrt(pow(Ax,2)+pow(Az,2)))*180/M_PI;
	

	printf("GOC X = %f\n", pitch);
	delay(1000);
	//printf("GOC Y = %d\n", roll);
	wiringPiI2CReadReg8(mpu,58); //xóa cờ ngắt
}

void read_mpu_in( void )
{
	read_mpu();
} 

int main(void)
	{
		// Setup giao tiếp I2C
		wiringPiSetupPhys();
		pinMode( INT, INPUT);
		mpu = wiringPiI2CSetup(0x68);	//  Địa chỉ muốn giao tiếp
		//printf("the mcp: %d\n", mpu);
		// Thiết lập chế độ đo cho MPU - 6050
		Init_6050();
		wiringPiISR(INT,INT_EDGE_RISING,&read_mpu_in);
		while(1)
		{
		
		//read_mpu();
		/* int16_t high = wiringPiI2CReadReg8(mpu, 59);
		int16_t low = wiringPiI2CReadReg8(mpu, 60);
		int16_t data = (high<<8) | low;
		printf("the read sensor: %d\n", data);
		delay(500); */
		
		}
		return 0;
	}
	