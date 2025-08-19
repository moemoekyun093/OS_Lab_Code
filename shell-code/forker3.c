#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int cc=fork();
    if(cc == 0)
    sleep(200);
    else
     ;
}