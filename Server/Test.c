#include<stdio.h>
#include<stdint.h>
#include<string.h>
int main()
{
    uint8_t buff[10];

    printf("The result of sizeof() operator is %lu\n",sizeof(buff));
    printf("The result of sizeof() with char* casting operator is %lu\n",sizeof((char*)buff));

    printf("The result of strlen() is %lu\n",strlen(buff));
    printf("The result of strlen() with char* casting is %lu\n",strlen((char*)buff));



    return 0;
}