#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sigint_handler(int sig) {
printf("yeh behen ka lauda phir se aa aa gaya\n");
}
int main() {
while(1)
{
    printf("hehe\n");
    sleep(1);
    signal(SIGINT, sigint_handler);
}


}