#include "common.h"
#include<string.h>

int main(int argc, char** argv)
{
    int listenfd, connfd, n;
    struct sockaddr_in serveraddr;
    uint8_t buff[MAXLINE];
    uint8_t recvline[MAXLINE];

    //Creating a socket

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        err_n_die("Socket creation error");
    }

    memset(&serveraddr,0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind to the address
    if((bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))) < 0)
    {
        err_n_die("Binding failed");

    }

    // Make the socket passive using listen()
    if((listen(listenfd,10 )) < 0 )
    {
        err_n_die("listen() failed");
    }


    while(1)
    {  
        struct sockaddr_in addr;
        socklen_t addr_len;
        char client_addr[MAXLINE+1];

    
        printf("Waiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        connfd = accept(listenfd, (struct sockaddr*)&addr, &addr_len);

        inet_ntop(AF_INET, &addr,client_addr, MAXLINE); //Network to presentation address
        printf("Client Addres is %s\n",client_addr);

        memset(recvline, 0, MAXLINE);

        while((n = read(connfd, recvline, MAXLINE-1)) > 0)
        {
            fprintf(stdout,"%s \n %s \n", bin2hex(recvline, n),recvline);

            if(recvline[n-1] == '\n')
            break;

            memset(recvline, 0, MAXLINE);


        }

        if(n < 0)
        err_n_die("Error while reading");

        snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\n Hello KK Server");
        
        // Be careful about sizeof() and strlen()
        write(connfd, (char*)buff, strlen((char*)buff)); // sizeof (buff) is not working
        close(connfd);

    }

    return 0;

    
}