

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

int stopflag = 0;


class Serial {
 std::string command;
 char read_msg_[40];
 std::stringstream ss;
 boost::asio::io_service m_io;
 boost::asio::serial_port m_port;
 boost::asio::deadline_timer m_timer1; //timer read
 boost::asio::strand m_strand;	 

public:
    
void my_read(){
  int read_size=m_port.read_some(boost::asio::buffer(read_msg_,40));
  read_msg_[read_size]=0;
  ss<<read_msg_;
  if(read_msg_[read_size-1]=='\n'){
		std::cout << ss.str();
		ss.str("");
  }
  m_timer1.async_wait(m_strand.wrap(boost::bind(&Serial::my_read, this)));
  
}

void my_write(){
	/*boost::array<char, 128> buf;
	std::copy(message.begin(),message.end(),buf.begin());	
	m_port.write_some(boost::asio::buffer(buf,20));*/
	
}

 

    Serial(const char *dev_name) : m_io(), m_port(m_io, dev_name), m_strand(m_io),m_timer1(m_io, boost::posix_time::seconds(1))
      {
      boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io)); //thread per l'io
	  m_timer1.async_wait(m_strand.wrap(boost::bind(&Serial::my_read, this))); //thread per la gestione dei read
	 
      }

};


void input_func(){
    while(true && !stopflag)
    {
        std::string input;
        std::cin >> input;
        std::cout << "Input: " << input << std::endl;
    }
}

int main(int argc, char* argv[])
{
  Serial s(argv[1]);
  std::thread inp(input_func);    
  
  sleep(100);
   
  return 0;

} 


