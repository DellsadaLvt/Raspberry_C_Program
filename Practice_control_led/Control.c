#include 	<wiringPi.h>
#include 	<mysql.h>
#include  	<stdio.h>
#include	<softPwm.h>
#include	<stdlib.h>
#include	<stdint.h>


#define Red 	11
#define Green	13
#define Blue	15 


void PwmLed( char led, uint8_t i );


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
	
	// softPwm config
	softPwmCreate( Red, 0, 100 );
	softPwmCreate( Blue, 0, 100 );
	softPwmCreate( Green, 0, 100 );
	

    while(1){
		
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
		
        // kiem tra cot isUpdated
        char sql[200];
        sprintf(sql, "select * from stateLed");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 
        row = mysql_fetch_row(res); //row[0]-> red; row[1]->green
        // NOTES: row la bien dang chuoi ky tu
        /*if( atoi(row[4])==1){
 
        }*/
		
		softPwmWrite(Red, (atoi(row[1]))*25/64);
		softPwmWrite(Blue, (atoi(row[2]))*25/64);
		softPwmWrite(Green, (atoi(row[3]))*25/64);
		delay(500);
		mysql_close(conn);
    }

    return 0;
}

/*void PwmLed( char led, uint8_t i ){
	int result = (atoi(row[i]))*25/64;
	softPwmWrite(led, result);	
	printf("%d\n", result);
}*/
	

/*$ gcc -o output_file $(mariadb_config --cflags)
source_code.c $(mariadb_config --libs)*/
/* gcc -o output_file $(mariadb_config --cflags) c_pro.c $(mariadb_config --libs) -lwiringPi
*/