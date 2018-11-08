#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>	
#include <iterator>
#include <vector>
#include <sstream>
#include <unistd.h>


class SimpleSerial
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
	SimpleSerial(std::string port, unsigned int baud_rate): io(), serial(io,port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
		serial.set_option( boost::asio::serial_port_base::character_size( 8 ) );
		serial.set_option( boost::asio::serial_port_base::parity() );	
		serial.set_option( boost::asio::serial_port_base::stop_bits() );
		
	}

    /**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void writeString(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }

    /**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
    std::string readLine()
    {	
	//Reading data char by char, code is optimized for simplicity, not speed
        using namespace boost;
	char c;
    std::string result;   
	boost::system::error_code ec;		
	for(;;)
        {
						
			asio::read(serial,asio::buffer(&c,1),ec);
			if(!ec){    
			switch(c)
            {
                case '\r':
					std::cout<< "terminatore riga" << std::endl;                     
					return result;
                case '\n':
					std::cout<< "a capo" << std::endl;                          
					return result;
                default:
                    result+=c;
            }}
			else{
				std::cout<< ec << std::endl;			
			}
			
			
		}
			
	}
	
		
	
    

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};

