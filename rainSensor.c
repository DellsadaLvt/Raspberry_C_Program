#include <wiringPi.h>
#include <stdio.h>

#define	sensor 22


int main( void ){
	wiringPiSetupPhys();
	
	pinMode( sensor, INPUT);
	
	while(1){
		if( digitalRead(sensor)){
			printf( "read digital\n" );
		}
		else{
			printf("not read \n");
		}
		delay(1000);
	}
	
	return 0;
}

/*
/***********************************
* NOTES: row la bien dang chuoi ky tu
        if( atoi(row[4])==1){
        }
*
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
#define   led0	11
#define   led1	13
#define   led2	15
#define   led3	16
#define   motor 18

#define   bt0   33
#define	  bt1	35
#define   bt2   37
#define   bt3	31 			// control 18 


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
	
	
    // Interrupt
	wiringPiISR( bt0, INT_EDGE_RISING, &handleBt0);
	wiringPiISR( bt1, INT_EDGE_RISING, &handleBt1);
	wiringPiISR( bt2, INT_EDGE_RISING, &handleBt2);
	wiringPiISR( bt3, INT_EDGE_RISING, &handleBt3);
	// softPwm config
	
	
	// create var
	char sql[200];
	unsigned long time=0;
	flag0 = flag1 = flag2 = flag3 =  0;
	en0 = en1 = en2 = en3 =  0;
	
	// Config interrupts 
	
	// Message
	printf("Successful!\n");


	/*----------- LOOP ----------*/
    while(1){
		
		if( millis() -time > 500){
			time = millis();
	
			/*============== DATABASE FORM =============*/
			// ket noi database
			conn = mysql_init(NULL);
			mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
			
			
			/*======================= USER SECTION ====================*/
			if ( en0 ){
				if( flag0){
					sprintf(sql, "update control set stateLed0= 'on'");	
				}else{
					sprintf(sql, "update control set stateLed0='off'");
				}
				mysql_query(conn, sql);
			}
			
			if ( en1 ){
				if( flag1){
					sprintf(sql, "update control set stateLed1= 'on'");	
				}else{
					sprintf(sql, "update control set stateLed1='off'");
				}
				mysql_query(conn, sql);
			}
			
			if ( en2 ){
				if( flag2){
					sprintf(sql, "update control set stateLed2= 'on'");	
				}else{
					sprintf(sql, "update control set stateLed2='off'");
				}
				mysql_query(conn, sql);
			}
			
			if ( en3 ){
				if( flag3 ){
					sprintf(sql, "update control set stateFan= 'on'");	
				}else{
					sprintf(sql, "update control set stateFan='off'");
				}
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
			if( !strcmp(row[1], "1") || en0){
				controlLed( row[2], led0);
				en0 = 0;
			}
			
			if( !strcmp(row[1], "1") || en1){
				controlLed( row[3], led1);
				en1= 0;
			}
			
			if( !strcmp(row[1], "1") || en2){
				controlLed( row[4], led2);
				en2= 0;
			}
			
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

*/