#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int idata = 111;

int main(int argc, char *argv[])
{

    int istack = 12;
    pid_t childpid;

    /*     using fork in the child process returns 0, while in the parent the fork
    returns the pid of the child, in case of the failure returns -1     */
    switch (childpid = fork())
    {
    case -1:
        /* code */
        printf("cannot create child!");
        break;
    case 0:
        istack *= 2;
        idata *= 3;
        break;
    default:
        sleep(3);
        break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(),
           (childpid == 0) ? "(child) " : "(parent)", idata, istack);

    return 0;
}
