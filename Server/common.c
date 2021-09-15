#include "common.h"


void err_n_die(const char* format, ...)
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

char* bin2hex(const unsigned char* input, size_t len)
{
    char* result;
    char* hexits = "0123456789ABCDEF";

    if(input == NULL || len <= 0)
    return NULL;

    int resultlength = (3*len)+1;

    result = malloc(resultlength * sizeof(char));

    memset(result, 0, resultlength);

    for(int i=0; i<len; i++)
    {
        result[i*3] = hexits[input[i] >>4];
        result[(i*3) + 1] = hexits[input[i] & 0X0F];
        result[(i*3) + 2] = ' ';
    }

    return result;


}