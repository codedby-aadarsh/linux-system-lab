#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_LEN 30

int count_words(char *buffer);
int count_lines(char *buffer);
int count_chars(char *buffer);

int main(int argc, char *argv[]){

    if(argc!=2 || strncmp(argv[1],"--help",6)==0){
        write(STDOUT_FILENO,"usage: wc file_name",20);
        return -1;
    }
    int iflag;
    int lines,words,charc;
    size_t numread;
    char buffer[MAX_LEN+1];
    char linebuf[100];
    iflag=open(argv[1],O_RDONLY);
    if(iflag<0){
        write(STDOUT_FILENO,"no such file or directory",26);
        return -1;
    }
    while((numread=read(iflag,buffer,MAX_LEN))>0){
        buffer[numread]='\0';
        words+=count_words(buffer);
        //lines+=count_lines(buffer);
        //charc+=count_chars(buffer);
    }
    snprintf(linebuf,sizeof(linebuf),"words:%d",words);
    write(STDOUT_FILENO,linebuf,sizeof(linebuf));

    if(close(iflag)==-1){
        write(1,"error closing file\n.",21);
        return -1;}

return 0;
}

int count_words(char* buffer){
    int words=0;
    while(*buffer++){
        if(*buffer==' ')
            words++;
    }
    return words;
}