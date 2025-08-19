#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/msg.h>

int main(int argc, char* argv[])
{
    void* ptr=fopen(argv[1],"r");
    msgrcv();
}