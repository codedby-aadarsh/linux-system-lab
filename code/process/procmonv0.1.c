#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_PATH "/proc/self/status"

int main(){

    FILE *fd = fopen(FILE_PATH,"r");
    char buffer[256];

    while(fgets(buffer,sizeof(buffer),fd)>0){
        if(strstr(buffer,"Name:")||strstr(buffer,"Pid:")||strstr(buffer,"VmRSS:"))
            printf("%s",buffer);
    }

    fclose(fd);
    return 0;
}