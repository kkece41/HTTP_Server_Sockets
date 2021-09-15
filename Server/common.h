#ifndef _COMMON_H_
#define _COMMON_H_

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

#define SERVER_PORT 1035
#define MAXLINE 4096

void err_n_die(const char* format, ...);
char* bin2hex(const unsigned char* input, size_t len);


#endif

