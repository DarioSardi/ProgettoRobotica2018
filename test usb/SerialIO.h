#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <thread>



class SerialIO{
private:
	boost::asio::io_service io_svc;
    boost::asio::serial_port m_port;
public:    
	


SerialIO(std::string portDir):m_port(io_svc,portDir){}

void write(std::string input){	
	const int BUFFSIZE=20;	
	boost::array<char,BUFFSIZE> buf;
	if(sizeof(input)>0){
		for(int i=0;i<sizeof(input)/8;i++){		
			buf[i]=input[i];
		}
		buf[sizeof(input)/8]=0;
		m_port.write_some(boost::asio::buffer(buf,sizeof(input)));
	}
}


void read(){
	const int BUFFSIZE=10;
	char read_msg_[BUFFSIZE];
    std::stringstream ss;
	int read_size=0;
	read_size=m_port.read_some(boost::asio::buffer(read_msg_,BUFFSIZE));
	while(read_msg_[read_size-1]!='\n'){	//ciclo fino al finestringa, in questo caso \n
	read_msg_[read_size]=0;		//array pieno di schifo, per evitare la copia di roba random metto il terminatore manualmente  	
	ss<<read_msg_;
	read_size=m_port.read_some(boost::asio::buffer(read_msg_,BUFFSIZE));  	
  	}
	read_msg_[read_size]=0;
	ss<<read_msg_;
	std::cout << ss.str();
}

};

