#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include <iostream>
#include <string.h>

#define BUF_SIZE 1024
char addr[30]="";
int search(void)
{
    FILE *f;
    char* buf;

    f=popen("./finder.o | grep Arduino | awk '{print $1;}' ", "r");
    if (f==NULL) {
        perror("1 - Error");
        return errno;
    }

   buf=(char*)malloc(BUF_SIZE);
   if (buf==NULL) {
        perror("2 - Error");
        pclose(f);
        return errno;
    }
	while(fgets(buf,BUF_SIZE,f)!=NULL) {    
		//printf("arduino found at: %s",buf);
		strcpy(addr,buf); //copia l'ultimo risultato
    }
    pclose(f);
    free(buf);

    return 0;
}

char* getArduino(){
	search();
	return addr;
}

