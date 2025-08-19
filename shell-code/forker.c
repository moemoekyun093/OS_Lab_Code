#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{   int status;
    int cc = fork();
    if(cc==0)
    {
       printf("%d",getpid());
       exit(4);
       
    }
    else 
    {
        fork();
        int n = waitpid(cc,&status,0);
        printf("%d",n);
        printf("%d\n",cc);
    }
}