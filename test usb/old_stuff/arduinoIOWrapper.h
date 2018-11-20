#include "boost3.h"
#include <thread>

class ArduinoIOWrapper{
private:
	ArduinoIO arduino;
public:
	ArduinoIOWrapper(std::string port):arduino(port){}
	void blockingRead(){
		arduino.read();	
	}
	void readThreadStart(){
		std::thread read(&ArduinoIO::read,arduino);
	}
	
	void write(std::string input){
		arduino.write(input);
	}
};
