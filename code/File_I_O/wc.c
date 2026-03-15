#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_LEN 30
#define BUF_SIZE 64

int count_words(char *buffer);
int count_lines(char *buffer);
int count_chars(char *buffer);

int main(int argc, char *argv[]){

    if(argc!=2 || strncmp(argv[1],"--help",6)==0){
        write(STDOUT_FILENO,"usage: wc file_name",20);
        return -1;
    }
    int iflag,lines=0,words=0,charc=0,len=0;
    size_t numread;
    char buffer[MAX_LEN+1];
    // do i have to initiaise it to zero is there any affect
    char linebuf[BUF_SIZE],wordbuf[BUF_SIZE],charbuf[BUF_SIZE];
    
    iflag=open(argv[1],O_RDONLY);
    if(iflag<0){
        write(STDOUT_FILENO,"no such file or directory",26);
        return -1;
    }
    while((numread=read(iflag,buffer,MAX_LEN))>0){
        buffer[numread]='\0';
        words+=count_words(buffer);
        lines+=count_lines(buffer);
        charc+=count_chars(buffer);
    }
    //null terminates the string automatically 
    char *buf[]={linebuf,wordbuf,charbuf};
    char *names[]= {"lines","words","characters"};
    int nums[]={lines,words,charc};
    // int len = snprintf(linebuf,sizeof(linebuf),"words:%d",words);
    //sizeof(buf[i]) : REMOVED THIS AS IT OUTPUT 8 BYTES AS address of pointer is of char type
    for(int i=0;i<3;i++){
        len = snprintf(buf[i],BUF_SIZE,"%s: %d\n",names[i],nums[i]);
        write(STDOUT_FILENO,buf[i],len);
    }
    if(close(iflag)==-1){
        write(1,"error closing file\n.",21);
        return -1;}

return 0;
}
int count_lines(char* buffer){
    int lines=0;
    while(*buffer){
        if(*buffer=='\n')
	        lines++;
        buffer++;
	}    
    return lines;
}
int count_chars(char* buffer){
    int chars=0;
    while(*buffer){
        chars++;
        buffer++;
    }
    return chars;
}
int count_words(char* buffer){
    int words=0,isword=1;
    while(*buffer){
        if(*buffer==' '|| *buffer=='\n' || *buffer=='\t')
            isword=0;
	else if(!isword){
	isword=1;
	words++;
	}
	buffer++;
    }
    return words;
}
