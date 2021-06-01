/***********************************
* THE CODE CONTROL 4LEDS, ONE FAN AND GET THE SIGNAL OF RAIN SENSOR WITH BUTTON AND WEBSERVER
* APPLY SMARTHOME
* THE CODE WRITE BY LE VAN THO
* DATE UPDATE: 1/6/2021
***********************************/

/*================ LIBRARIES ===================*/
#include 	<mysql.h>
#include  	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>	
#include	<wiringPi.h>
#include	<time.h>
#include 	<string.h>


/*============== FUNCTION ===============*/
void controlLed( char *str , uint8_t led);
void updateFlag( uint8_t led, uint8_t mode);

/*============== IO ===============*/
#define   led0	 11
#define   led1	 13
#define   led2	 15
#define   led3	 16
#define   motor  18
#define	  sensor 22

#define   bt0   33			// control led0
#define	  bt1	35			// control led1
#define   bt2   37			// control led2
#define   bt3	31 			// control motor


/*============= DECLARE VARIABLES =========*/
volatile uint8_t flag0, flag1, flag2, flag3, en0, en1, en2, en3;


/*============== Interrupt func ===============*/
void handleBt0( void ){
	if( digitalRead( bt0 )){
		delay(5);
		if( digitalRead( bt0)){
			en0= 1;
			flag0 ^= 1; 
		}
	}
}

void handleBt1( void ){
	if( digitalRead( bt1 )){
		delay(5);
		if( digitalRead( bt1 )){
			en1 = 1;
			flag1 ^= 1; 
		}
	}
}

void handleBt2( void ){
	if( digitalRead( bt2 )){
		delay(5);
		if( digitalRead( bt2 )){
			en2 = 1;
			flag2 ^= 1; 
			
		}
	}
}

void handleBt3( void ){
	if( digitalRead( bt3 )){
		delay(5);
		if( digitalRead( bt3 )){
			en3 = 1;
			flag3 ^= 1; 
		}
	}
}


/*============== MAIN FUNCTION ===============*/
int main(void)
{
	/* Config mysql */
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "admin_10";
    char *password = "123456"; 
    char *database = "smartHome";
	
	
    // Setup thu vien wiringPi
	wiringPiSetupPhys();
	
	// setup io
	pinMode( led0, OUTPUT);
	pinMode( led1, OUTPUT);
	pinMode( led2, OUTPUT);
	pinMode( led3, OUTPUT);
	pinMode( motor, OUTPUT);
	
	pinMode( bt0,  INPUT);
	pinMode( bt1,  INPUT);
	pinMode( bt2,  INPUT);
	pinMode( bt3,  INPUT);
	
	
    // initial Interrupt
	wiringPiISR( bt0, INT_EDGE_RISING, &handleBt0);
	wiringPiISR( bt1, INT_EDGE_RISING, &handleBt1);
	wiringPiISR( bt2, INT_EDGE_RISING, &handleBt2);
	wiringPiISR( bt3, INT_EDGE_RISING, &handleBt3);
	
	
	
	// create and initial variables
	char sql[200];
	unsigned long time=0;
	unsigned char stateRain = 0;
	flag0 = flag1 = flag2 = flag3 =  0;
	en0 = en1 = en2 = en3 =  0;
	
	
	// Message
	printf("Successful!\n");


	/*----------- LOOP ----------*/
    while(1){
		
		if( millis() -time > 250){
			time = millis();
	
			/*============== DATABASE FORM =============*/
			// ket noi database
			conn = mysql_init(NULL);
			mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
			
			
			/*======================= USER SECTION ====================*/
			// update database in stateLed0 column when press button 0
			if ( en0 ){
				if( flag0){
					sprintf(sql, "update control set stateLed0= 'on'");	
				}else{
					sprintf(sql, "update control set stateLed0='off'");
				}
				mysql_query(conn, sql);
			}
			
			// update database in stateLed1 column when press button 1
			if ( en1 ){
				if( flag1){
					sprintf(sql, "update control set stateLed1= 'on'");	
				}else{
					sprintf(sql, "update control set stateLed1='off'");
				}
				mysql_query(conn, sql);
			}
			
			// update database in stateLed2 column when press button 2
			if ( en2 ){
				if( flag2){
					sprintf(sql, "update control set stateLed2= 'on'");	
				}else{
					sprintf(sql, "update control set stateLed2='off'");
				}
				mysql_query(conn, sql);
			}
			
			// update database in stateFan column when press button 3
			if ( en3 ){
				if( flag3 ){
					sprintf(sql, "update control set stateFan= 'on'");	
				}else{
					sprintf(sql, "update control set stateFan='off'");
				}
				mysql_query(conn, sql);
			}
			
			// update database in stateRain from rain sensor
			if( digitalRead( sensor) ^ stateRain ){
				stateRain = digitalRead(sensor);
				if( stateRain)
					sprintf(sql, "update control set stateRain= 'Raining'");
				else
					sprintf(sql, "update control set stateRain= 'Not Raining'");
				mysql_query(conn, sql);
			}
			
			
			/*============================================*/
			// get data from mysql
			sprintf(sql, "select * from control");
			mysql_query(conn,sql);
			res = mysql_store_result(conn); 	
			row = mysql_fetch_row(res); 
			/*============================================*/
			
			
			
			/*============== USER SECTION ===================*/
			// control led0
			if( !strcmp(row[1], "1") || en0){
				controlLed( row[2], led0);
				en0 = 0;
			}
			
			// control led1
			if( !strcmp(row[1], "1") || en1){
				controlLed( row[3], led1);
				en1= 0;
			}
			
			// control led 2
			if( !strcmp(row[1], "1") || en2){
				controlLed( row[4], led2);
				en2= 0;
			}
			
			// control led3
			if( !strcmp(row[1], "1")){
				controlLed( row[5], led3);
				en3= 0;
			}
			
			// control fan
			if( !strcmp(row[1], "1") || en3){
				controlLed( row[6], motor);
				en3= 0;
			}
			
			
			
			/*============== DATABASE FORM ==================*/
			sprintf(sql, "update control set ena=0");
			mysql_query(conn, sql);
			// disconnect database
			mysql_close(conn);
			/*===============================================*/
			
		}
		
    }

    return 0;
}



/*==================== SUBROUTINE ====================*/
void controlLed( char *str , uint8_t led){
	if ( !strcmp( str , "on")){
			digitalWrite( led, HIGH);
			updateFlag( led, 1);
		}
		else if( !strcmp( str , "off")){
			digitalWrite( led, LOW);
			updateFlag( led, 0);
		}
}


void updateFlag( uint8_t led, uint8_t mode){
	
	if( mode ){
		switch( led ){
			case 11:
				flag0 = 1;
				break;
			case 13:
				flag1 = 1;
				break;
			case 15:
				flag2 = 1;
				break;
			case 18:
				flag3 = 1;
				break;
			default:
				break;
			
		}
	}
	
	else if ( mode == 0 ){
		switch( led ){
			case 11:
				flag0 = 0;
				break;
			case 13:
				flag1 = 0;
				break;
			case 15:
				flag2 = 0;
				break;
			case 18:
				flag3 = 0;
				break;
			default:
				break;
		}
	}
}