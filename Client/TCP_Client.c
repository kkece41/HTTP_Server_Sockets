#include<sys/socket.h>
#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdarg.h>
#include<error.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<netdb.h>

#define SERVER_PORT 80
#define MAXLINE 4096

void error_n_die(const char* format,...);

int main(int argc, char** argv)
{
    int sockfd, n;
    int sendbytes;
    struct sockaddr_in serveraddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];


    if(argc!=2)
    {
        error_n_die("usage: %s <server address>",argv[0]);
    }

    /* Create a socket */
    sockfd = socket(AF_INET,SOCK_STREAM,0); // 0 indicates default protocol, which is TCP 
    if(sockfd<0)
    {
        error_n_die("Erros during creation of socket");
    }

    // The bzero() function is deprecated (marked as LEGACY in
    //POSIX.1-2001); use memset(3) in new programs.
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT); // host to network short

    if(inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0) //convert string format to binary . Examples  "123.34.34.54" to binary .
     {
        error_n_die("Error during inet_pton()  %s",argv[1]);
    }

    // Connect to a Server
    if(connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) <0 )
    {
        error_n_die("Error during socket connection to the server");
    }

    //We are connected to the server
    //Prepare the HTTTP reqest data to be sent
    sprintf(sendline,"GET / HTTP/1.1\r\n\r\n"); // Here / means root
    sendbytes = strlen(sendline);

    // Send the HTTP request using write
    if(write(sockfd, sendline, sendbytes) != sendbytes)
    {
        error_n_die("Write failed");
    }

    memset(recvline, 0,MAXLINE);

    while( (n = read(sockfd, recvline, MAXLINE-1)) >0 )
    {
        printf("%s",recvline);
    }

    if(n < 0) 
    error_n_die("Read failed");

    close(sockfd);

    exit(0);

}

void error_n_die(const char* format,...)
{
    int errno_save;
    va_list ap;

    errno_save = errno;

    //print out the format+args to standard output
    va_start(ap,format);
    vfprintf(stdout,format, ap);
    fprintf(stdout,"\n");
    fflush(stdout);

    if(errno_save!=0)
    {
        fprintf(stdout, "(errno = %d): %s\n",errno_save,strerror(errno_save));
        fprintf(stdout,"\n");
        fflush(stdout);
    }

    va_end(ap);

    exit(0);

}