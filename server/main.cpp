/*

* Author:       Rick Candell (rick.candell@nist.gov)
*
* Organization: National Institute of Standards and Technology
*               U.S. Department of Commerce
* License:      Public Domain

*/
// rtclient.cpp : Defines the main() entry point for the console application.
//

#include <boost/system/config.hpp>
#include <boost/program_options.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::udp;

#define CMD_SHMEM_NAME ("cmd_shmem")

#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <utility>

#include <common.h>


using boost::asio::ip::udp;
using namespace std;

int main(int argc, char* argv[])
{
	// program option variables
	unsigned serverPort = 17998;
	string bindAddr = "127.0.0.1";


	// program options
	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h",													"print the help message")
		("port,p",		po::value<unsigned>(&serverPort),			"server port number")
		("addr,a",		po::value<string>(&bindAddr),				"bind address")
		;

	po::variables_map vm;
	try	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		if (vm.count("help"))
		{
			std::cout << desc << std::endl;
			return 0;
		}

		po::notify(vm);
	}
	catch (po::error& e) {
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << desc << std::endl;
		return 0;
	}

	// set up the shared memory for the command messages to the ROS controller
	using namespace boost::interprocess;
	try
	{
		if (vm.count("x"))
		{
			shared_memory_object msg_shm(open_only, CMD_SHMEM_NAME, read_write);
			mapped_region reg_msg(msg_shm, read_write);
		}
	}
	catch (interprocess_exception & ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}

	// UDP server
	try
    {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), serverPort));
        std::cout << "Created UDP listener socket on port: " << serverPort << std::endl;
        for (;;)
        {
            udp::endpoint remote_endpoint;
            VelocityControllerMessage msg;
            socket.receive(
                boost::asio::buffer((void *)&msg,
                sizeof(VelocityControllerMessage))
            );

            // print what we received
            std::cout << msg << std::endl;

            // write data to shared memory

        }

      }
      catch (std::exception& e)
      {
        std::cerr << e.what() << std::endl;
      }


    // close UDP socket


	return 0;
}
