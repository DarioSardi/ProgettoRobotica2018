#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

void* serial_rx_thread(void *port)
{
        unsigned char buf[100], *p;
        //ROS_INFO("%s: called", __FUNCTION__);
        ros::Rate loop_rate(100);  // run 100 times per second
        static int rx_cnt = 0;
    	int eof_cnt = 0;

        while (serial_rx_thread_running)
        {
        memset(buf, 0x0, sizeof(buf));
        p = buf;
        try {
            while (1) {
                char c;
                size_t cnt;
                // read 1 byte into c, this will block forever if no character
                // arrives
                cnt = asio::read(m_arduino_serial, asio::buffer(&c,1));
                rx_cnt++;
                if (c != '\n') {
                    if (c == '[') {
                        //ROS_INFO("<<<%s: got start [", __FUNCTION__);
                    }
                    *p = c;
                    p++;
                    continue;
                } else
                {
                    string s = string((char *)buf);
                    serial_rx_q.push(s);
                    //ROS_INFO("<<<%s: got line break. eof_cnt %d. buf %s. ", __FUNCTION__, eof_cnt, buf);
                    arduinoAcked = true;
                    break;
                }
            }
        } catch (std::exception& e) {
            //std::cerr << e.what() << std::endl;
            eof_cnt++;
        }
                loop_rate.sleep();
        }
        //ROS_INFO("%s: exit", __FUNCTION__);
        pthread_exit(NULL);
}

void* serial_tx_thread(void *port)
{
        ROS_INFO("%s: called", __FUNCTION__);
        ros::Rate loop_rate(100);  // run 100 times per seconds
        static int tx_cnt = 0;

        while (serial_tx_thread_running)
        {
                if (serial_tx_q.size() != 0 && arduinoAcked == true)
                {
                        string s;
                        int cnt;
                        s = serial_tx_q.front();
                        serial_tx_q.pop();
                        boost::system::error_code ec;
                        cnt = m_arduino_serial.write_some(boost::asio::buffer(s.c_str(), s.size()),ec);
                        if (cnt != 0)
                        {
                                //ROS_INFO(">>>%s: sending %s, tx_cnt %u",
                                                 __FUNCTION__, s.c_str(), tx_cnt++);
                                if (s.compare("st") == 0)
                                {
                                        arduinoAcked = false;
                                }
                        }
                }
                loop_rate.sleep();
        }
        //ROS_INFO("%s: exit", __FUNCTION__);
        pthread_exit(NULL);
}

asio::io_service _io;
asio::serial_port m_arduino_serial(_io);

main()
{
    m_arduino_serial.open(port);
    m_arduino_serial.set_option(asio::serial_port_base::baud_rate(baud));
    ...
    //spawn two threads...
    //every 10 seconds
    serial_tx_q.push("st");
    ...
}
