#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
clude <string.h>

int main(int argc, char *argv[]){

if(argc!=2 || strcmp(argv[1],"--help")==0){
 printf("usage: cat file_name\n");
printf("%d",argc); 
return -1;
}
int inputflag;
char buffer[30+1];
size_t numread;
inputflag= open(argv[1],O_RDONLY);
if(inputflag==-1){
printf("error:file doesnt exists!!");
return -1;
}

/*
*you dont provide the file path like as argv[1], why because when you open the file
*by the open it returns a file descriptor lowest one available and you pass that in 
*read  
*/
while((numread=read(inputflag,buffer,sizeof(buffer)))>0){
// printf("%ld\n",numread); 
buffer[numread]='\0';
write(STDOUT_FILENO,buffer,numread);}

if(close(inputflag)==-1)
	printf("error closing file");


return 0;
}
