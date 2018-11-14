#include <iostream>	
#include "boost3.h"
#include <unistd.h>
using namespace std;
using namespace boost;
string input;


int main(int argc, char* argv[])
{
    ArduinoIO a("/dev/ttyACM3");
	sleep(3);	
	while(1){	
	a.write("ciao");
	a.read();
	sleep(1);	
	}
	
}
