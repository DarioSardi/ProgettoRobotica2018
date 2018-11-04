#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // for usleep()
#include <getopt.h>

#include "arduino-serial-lib.h"
void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    const int buf_max = 100;

    int fd = -1;
	char *port="/dev/ttyACM3";
    int baudrate = 9600;  // default
    char eolchar = '\n';
    int timeout = 5000;
    char buf[buf_max];
    int rc,n;
    fd = serialport_init(port, baudrate);
	if( fd==-1 ) error("couldn't open port");
    printf("opened port %s\n",port);
    serialport_flush(fd);
	while(1){
		memset(buf,0,buf_max);  //
		serialport_read_until(fd, buf, eolchar, buf_max, timeout);
		if(buf[0]!=0) printf("-%s", buf);
	}
}
