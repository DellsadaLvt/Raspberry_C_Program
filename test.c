#include <stdio.h>
#include <string.h>



int main( void ){
	
	char str[20] = "Hi \0";
	
	printf("the str: %s\n", str);
	strcat(str, "Hello World!");
	printf("the str after: %s\n", str);
	return 0;
}

