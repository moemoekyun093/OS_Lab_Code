#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main()
{
    char* a = "/bin/ls";
    execlp("cat","cat","exec.c",NULL);
}