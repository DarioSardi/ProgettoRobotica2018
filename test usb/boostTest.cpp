/* compile with
  g++ -std=gnu++11 -o boost boostTest.cpp -lboost_system -lboost_thread -pthread
*/

#include <iostream>	
#include "SerialIO.h"
#include "deviceFinder.h"
#include <unistd.h>
#include <thread>
#include <string>
using namespace std;
using namespace boost;
string input;


int main(int argc, char* argv[])
{
	
	//std::cout<<"creo interfaccia....";	 
	printf("connecting to arduino at %s\n",getArduino());   
	SerialIO a(getArduino());
	//std::cout<<"ok!\n";	
	sleep(2); //arduino è lento a svegliarsi...	
	while(1){								
					std::cout<<"IO:ciao Arduino!\nArduino:";	
	a.write("ciao");
	a.read();
					std::cout<<" "<<std::endl;
	}
	
}
