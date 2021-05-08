#include <wiringPi.h>
#include <mysql.h>
#include  <stdio.h>

void xuly_ngat(void){
    // cap nhat xung PWM

    // update database


}

int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "admin_3";
    char *password = "123456"; /* set me first */
    char *database = "ledControl";
    // setup thu vien wiringPi
    wiringPiSetup();

    // Khai bao IO, interrupt, softPWM

    while(1){
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
        // kiem tra cot isUpdated
        char sql[200];
        sprintf(sql, "select * from rgbValue");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 
        row = mysql_fetch_row(res); //row[0]-> red; row[1]->green
        // NOTES: row la bien dang chuoi ky tu
        /*if( atoi(row[4])==1){

 
        }*/
		printf("%s\n", row[0]);
		delay(500);
		mysql_close(conn);
    }

    return 0;
}

/*$ gcc -o output_file $(mariadb_config --cflags)
source_code.c $(mariadb_config --libs)*/
/* gcc -o output_file $(mariadb_config --cflags) c_pro.c $(mariadb_config --libs) -lwiringPi
*/