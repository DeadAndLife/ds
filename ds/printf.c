#include <stdio.h>
#include <unistd.h>
int main(void) 
{
    printf("Hello, world!111\n");
    fprintf(stderr, "Hello, world!222");
    sleep(100);
    return 0;
}
