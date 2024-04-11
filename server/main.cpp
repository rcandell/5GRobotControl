/*

* Author:       Rick Candell (rick.candell@nist.gov)
*
* Organization: National Institute of Standards and Technology
*               U.S. Department of Commerce
* License:      Public Domain

*/
// main.cpp : Defines the main() entry point for the console application.
//

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

	// UDP server
	try
    {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), serverPort));
        std::cout << "Created UDP listener socket on port: " << serverPort << std::endl;
        for (;;)
        {
            udp::endpoint remote_endpoint;
            char msg[256];
            socket.receive(
                boost::asio::buffer((void *)&msg,
                sizeof(msg)
            ));

            std::cout << "received a message" << std::endl;
            std::cout << msg << std::endl;

            // print what we received
            std::istringstream ssin(msg);
            VelocityControllerMessage vcmsg;
            ssin >> vcmsg;
            std::cout << vcmsg << std::endl<< std::endl;

            // convert to "twist" type of ROS message

            // Publish to ROS "twist" topic

        }

      }
      catch (std::exception& e)
      {
        std::cerr << e.what() << std::endl;
      }


	return 0;
}
