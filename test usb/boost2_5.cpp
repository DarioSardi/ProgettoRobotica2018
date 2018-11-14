

/** BOOST ASIO SERIAL EXAMPLE 
  
  boost::asio::serial_port
  boost::asio::serial_port::async_read_some
  
  **/

/* compile with
  g++ -std=gnu++11 -o boost boost2.cpp -lboost_system -lboost_thread -pthread
  */

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
const int BUFFSIZE=60;
boost::asio::io_service io_svc;
boost::asio::serial_port m_port(io_svc,"/dev/ttyACM3");
char read_msg_[BUFFSIZE];
std::stringstream ss;
std::string input;
boost::system::error_code ec;


void my_write(){	
	if(input!=""){
	boost::array<char, BUFFSIZE> buf;
	for(int i=0;i<sizeof(input)/8;i++){		
		buf[i]=input[i];
	}
	input[sizeof(input)]=0;
	for(int k=sizeof(input)/8;k<BUFFSIZE;k++){buf[k]=0;} 
	int sent=m_port.write_some(boost::asio::buffer(buf,sizeof(input)));
	input="";
	}
}


void my_read(){
  while(1){
  int read_size=0;
  read_size=m_port.read_some(boost::asio::buffer(read_msg_,BUFFSIZE));
  if(read_size>0){
  read_msg_[read_size]=0;
  ss<<read_msg_;
  if(read_msg_[read_size-1]=='\n'){
		std::cout << ss.str();
		ss.str("");
  }
  }}
}

void input_func(){
      while(1){
		std::cin >> input;
		//std::cout << "Input inviato: " << input << std::endl;
		my_write();}
}

int main(int argc, char* argv[])
{
  for(int k=0;k<BUFFSIZE;k++){
	read_msg_[k]=0;
	}
  std::thread read(my_read);
  std::thread inp(input_func);
  //std::thread write(my_write);
  while(1){}
} 


