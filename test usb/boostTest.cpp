#include <iostream>	
#include "SimpleSerial.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
    try {

        SimpleSerial serial("/dev/ttyACM3",9600);
	cout<<serial.readLine();
        serial.writeString("Hello world\n");
	
	cout<<"begin read phase"<<endl;
	while(1){	
	serial.writeString("Hello world\n");	
	cout<<serial.readLine();
	}
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }
}
