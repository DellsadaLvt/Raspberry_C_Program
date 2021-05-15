/***********************************
* NOTES: row la bien dang chuoi ky tu
        if( atoi(row[4])==1){
        }
*
***********************************/
#include 	<wiringPi.h>
#include 	<mysql.h>
#include  	<stdio.h>
#include	<softPwm.h>
#include	<stdlib.h>
#include	<stdint.h>
#include    <stdbool.h>
#include    <string.h>	


#define Red 	11
#define Green	13
#define Blue	15 
#define btnr  	31
#define btng	33
#define btnb	35
#define btnena	37


volatile bool flag= 0;
volatile uint8_t red_light=0, blue_light= 0;

void PwmLed(uint8_t mode,  uint8_t *numb);


void handle_btnr( void ){
	if( digitalRead(btnr)){
		delay(5);
		if(digitalRead( btnr )){
			flag = 1;
			red_light += 20;
			if( red_light >= 250){
				red_light = 0;
			}
		}
	}
}

void handle_btnb( void ){
	if( digitalRead(btnb)){
		delay(5);
		if(digitalRead( btnb )){
			flag = 1;
			blue_light += 20;
			if( blue_light >= 250){
				blue_light = 0;
			}
		}
	}
}


int main(void)
{
	/* Config mysql */
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "admin_6";
    char *password = "123456"; 
    char *database = "prac_rgb";
	
	
    // setup thu vien wiringPi
    wiringPiSetupPhys();


    // Khai bao IO, interrupt, softPWM
	pinMode( Red, 	OUTPUT );
	pinMode( Green, OUTPUT );
	pinMode( Blue, 	OUTPUT );
	pinMode( btnr,	INPUT  );
	pinMode( btng, 	INPUT  );
	pinMode( btnb, 	INPUT  );
	pinMode( btnena,INPUT  );
	
	
	// softPwm config
	softPwmCreate( Red, 0, 100 );
	softPwmCreate( Blue, 0, 100 );
	softPwmCreate( Green, 0, 100 );
	
	// create var
	char str[50];
	uint8_t numb[9];
	char sql[200];
	
	// Config interrupts 
	wiringPiISR(btnr, INT_EDGE_RISING, &handle_btnr);
	wiringPiISR(btnb, INT_EDGE_RISING, &handle_btnb);
	

    while(1){
		
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
		
		
		if( flag ){
			sprintf(sql, "update stateLed set red=%d, blue=%d", red_light, blue_light);
			mysql_query(conn, sql);
			flag = 0;
		}
	
	
        // get data from mysql
        sprintf(sql, "select * from stateLed");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 	
        row = mysql_fetch_row(res); //row[0]-> red; row[1]->green
		red_light = numb[1];
		blue_light = numb[2];
		
		
		
		
		for(int i=0; i<9; i++){
			numb[i]= atoi(row[i]);
		}
		stpcpy(str,row[6]);
		
		
		PwmLed(1, numb);
		//printf("rgb: %d  %d\n", red_light, blue_light);
		//delay(1000);
		
		mysql_close(conn);
    }

    return 0;
}

void PwmLed(uint8_t mode,  uint8_t *numb){
	
	static uint8_t temp_r, temp_g, temp_b;
	//printf("gia tri state: %d\n", *(numb+5));
	if( (temp_r != (*(numb + 1))) || (temp_g != (*(numb + 3))) ||  (temp_b != (*(numb + 2)))  ){
		temp_r = *(numb + 1);
		temp_g = *(numb + 3);
		temp_b = *(numb + 2);
		uint8_t pwm_r = (*(numb + 1))*25/64;
		uint8_t pwm_g = (*(numb + 3))*25/64;
		uint8_t pwm_b = (*(numb + 2))*25/64;
		
		softPwmWrite(Red,pwm_r );
		softPwmWrite(Green,pwm_g );
		softPwmWrite(Blue,pwm_b );
		printf("pwm changed\n");
	}

}
	

/*$ gcc -o output_file $(mariadb_config --cflags)
source_code.c $(mariadb_config --libs)*/
/* gcc -o output_file $(mariadb_config --cflags) c_pro.c $(mariadb_config --libs) -lwiringPi
*/