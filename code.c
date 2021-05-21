#include	<wiringPi.h>
#include 	<wiringSerial.h>
#include 	<string.h>
#include 	<mysql.h>
#include  	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>	




#define intPin 11

volatile char flag;


float getDataInt(int *fd);
void pushData(int *fd,char content[5]);
char* getDataStr( int *fd );


void handle_int( void ){
	flag=1;
	//printf("value i: %d\n", x);
}

int main( void ){
	
	/* Config mysql */
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
	
	char *server = "localhost";
    char *user = "admin_6";
    char *password = "123456"; 
    char *database = "MedicalHeight";
	char sql[200];
	
	
	int fd,input;
	float dis;
	fd = serialOpen("/dev/ttyAMA0", 9600);
	char temp;
	float height, weight;
	flag=0;
	
	/* SETUP WIRINGPI LIB */
	wiringPiSetupPhys();
	
	/* SETUP INTERRUPT  */
	wiringPiISR( 11 , INT_EDGE_RISING , &handle_int);
	
	printf("serial begin \n");
	
	
	
	
	while(1){
	/*============== DATABASE SECTION =============*/
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
		
        // get data from mysql
        sprintf(sql, "select * from hweight where id=(select max(id) from hweight)");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 	
        row = mysql_fetch_row(res); 
	
		if( atoi(row[7]) == 1){
		// update height
		pushData(&fd, "on");
		delay(100);
		if(flag >=1){
			dis = getDataInt(&fd);
			flag=0;
		}
		pushData(&fd, "off");
		
		sprintf(sql, "update hweight set ena= 0, height= %f where id= (select max(id) from hweight)", dis);
		mysql_query(conn, sql);
		}
		
		
		
		// disconnect database
		mysql_close(conn);
		
		delay(1000);
		/*============================================*/
		

		
		
	}
	
	serialClose(fd);
	
	
	
	return 0;
} 

float getDataInt(int *fd){
	int i=0, result, data[5]={0,0,0,0,0};
	float distance;
	while( serialDataAvail(*fd)){
		data[i] = serialGetchar(*fd) - 48;
		//printf("%d\n", data[i]);
		//printf("Successful %d \n\n", i);
		i++;
	}
	//printf("the value i: %d\n", i);
	if(i==3)
		result = data[0]*100 + data[1]*10 + data[2];
	if(i==4)
		result = data[0]*1000 + data[1]*100 + data[2]*10 + data[3];
	//printf("the result is: %d\n", result);
	distance = result/100.0;
	printf("the result is: %f\n", distance);
	//printf("\n\n\n");
	return distance;
	
}

void pushData(int *fd, char content[5]){
	char str[10];
	strcpy(str, content);
	serialPuts(*fd, str);
}


char* getDataStr( int *fd ){
	static char str[10];
	char i=0;
	
	for(int i=0; i< strlen(str); i++){
		str[i]= '\0';
	}
	
	while(serialDataAvail(*fd)){
		delay(10);
		if( serialDataAvail(*fd)){
			str[i] = serialGetchar(*fd); 
			i++;
		}
	}
	printf("the result is: %s\n", str);
	return str;
}
