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

    f=popen("./finder.o | grep Arduino | awk '{print $1;}'", "r");
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
		//printf("arduino found at: %s, len %d\n",buf,strlen(buf));
			
		for(int i=0;i<strlen(buf);i++){
			if(buf[i]==' '| buf[i]=='\n' ){
				//printf("find it\n");				
				buf[i]=0;			
			}	
			else{
				//printf("%c\n-",buf[i]);
			}	
		}
		strcpy(addr,buf); //copia l'ultimo risultato
    }
    pclose(f);
    free(buf);
    return 0;
}

char* getArduino(){
	search();
	//printf("%s-+-+-",addr);
	return addr	;
}

int main()
{
	getArduino();
	printf("%s cose",addr);
	return 0;
}

