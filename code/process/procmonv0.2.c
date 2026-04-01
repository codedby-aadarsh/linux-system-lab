#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


int main(){
    DIR *d = opendir("/proc");
    struct dirent *entry;

    while((entry=readdir(d))!=NULL){
        if(atoi(entry->d_name)==0) continue;
        char path[20],line[256];

        /*  line termination of path happens automatically*/
        if (snprintf(path,20,"/proc/%d/status",atoi(entry->d_name))<0)
            break;
        FILE *fp = fopen(path,"r");
        if(!fp){
            perror(path);
            break;}
        while(fgets(line,sizeof(line),fp)>0){
            if(strstr(line,"Name:")){
                printf("%s",line);
            }
        }
        fclose(fp);
    }
    closedir(d);        
    return 0;
}