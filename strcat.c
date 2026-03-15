#include <stdio.h>
#include <stdlib.h>

void mystrcat(char *dest,char *src);

int main(){
char dest[20] = "hello ";
char *src="aadarsh";

mystrcat(dest,src);
printf("%s",dest);
return 0;
}

void mystrcat(char *dest,char *src){

while(*dest){
	dest++;}
//printf("current value : %s",s);
while(*dest++=*src++)
	;
}
