#include <iostream>	
#include "SimpleSerial.h"

using namespace std;
using namespace boost;
string input;


int main(int argc, char* argv[])
{
    try {

    SimpleSerial serial("/dev/ttyACM3",9600);
	while(1){
	sleep(10);
	}	


	/*cout<<"begin read phase"<<endl;
	while(1){	
	cin >> input;	
	serial.writeString(input);	
	cout<<serial.readLine();
	}
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }*/
}
