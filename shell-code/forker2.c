#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int n;
    int c;
    int d=69;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
       c= fork();
       if( c==0)
        d=i;
        
    }
    if(d==69)
        d=-1;
    for(int i=0;i<n-d-1;i++)
    {
        wait(NULL);
    }
    printf("%d,\n",wait(NULL));
    exit(2);
}