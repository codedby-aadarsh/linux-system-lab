#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_LEN  30
int main(int argc,char *argv[]){

if(argc!=3 || strcmp(argv[1],"--help")==0){
write(STDOUT_FILENO,"usage: cp src_file dest_file\n",23);
return -1;
}
int ifile , ofile,oflag;
mode_t fileperms;
ssize_t numread;
char buf[MAX_LEN+1];
oflag = O_WRONLY | O_CREAT | O_TRUNC;
fileperms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; 
ifile=open(argv[1],O_RDONLY);
if(ifile<0){
	write(STDOUT_FILENO,"no such file\n",14);
	return -1;
}
ofile=open(argv[2],oflag,fileperms);
if(ofile<0){
write(STDOUT_FILENO,"can't create file\n",19);
goto exit;
}
while((numread=read(ifile,buf,MAX_LEN))>0){
if(write(ofile,buf,numread)!=numread){
write(STDOUT_FILENO,"some error\n",11);
goto exit;
}
}

if (close(ifile)==-1)
	write(STDOUT_FILENO,"error closing file 1\n",22);
if(close(ofile)==-1)
	write(STDOUT_FILENO,"error closing file 1\n",22);
return 0;
exit:
	if (close(ifile)==-1)
			write(STDOUT_FILENO,"error closing file 1\n",22);
	if(close(ofile)==-1)
			write(STDOUT_FILENO,"error closing file 1\n",22);
	return -1;
}
