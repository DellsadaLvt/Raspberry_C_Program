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


/*============== MAIN FUNCTION ===============*/
int main(void)
{
	/* Config mysql */
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "admin_6";
    char *password = "123456"; 
    char *database = "smartGarden";
	
	
    // setup thu vien wiringPi
    // Khai bao IO, interrupt, softPWM
	// softPwm config
	
	
	// create var
	uint8_t temp, humid;
	char sql[200];
	
	// Config interrupts 
	
	// Message
	printf("Successful!\n");


	/*----------- LOOP ----------*/
    while(1){
		
		/*========= SIMULATE RANDOM INPUT ========== */
		srand(time(NULL));
		temp= rand()%100;
		humid= rand()%100;
		/*==========================================*/
		
		
		
		/*============== DATABASE SECTION =============*/
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
		
        // get data from mysql
        sprintf(sql, "select * from tempAndHumid where id> ((select max(id) from tempAndHumid)-5)");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 	
        row = mysql_fetch_row(res); 
		
		// add date
		sprintf(sql, "insert into tempAndHumid (temperature, humid) values (%d, %d)", temp, humid);
		mysql_query(conn, sql);
		
		// disconnect database
		mysql_close(conn);
		/*============================================*/
		
		
		
		/*============== USER SECTION ===================*/
		//printf("Get data: %s\n", row[1]);
		delay(2000);
		/*===============================================*/
		
    }

    return 0;
}


	

/*$ gcc -o output_file $(mariadb_config --cflags)
source_code.c $(mariadb_config --libs)*/
/* gcc -o output_file $(mariadb_config --cflags) c_pro.c $(mariadb_config --libs) -lwiringPi
*/