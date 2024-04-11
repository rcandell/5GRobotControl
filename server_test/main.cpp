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
	string serverPort = "17998";
	string bindAddr = "127.0.0.1";


	// program options
	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h",													"print the help message")
		("port,p",		po::value<string>(&serverPort),			"server port number")
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
        udp::resolver resolver(io_context);
        std::cout << "Server: " << bindAddr << " Port: " << serverPort << std::endl;
        udp::endpoint receiver_endpoint =
          *resolver.resolve(udp::v4(), bindAddr, serverPort).begin();
        udp::socket socket(io_context);
        socket.open(udp::v4());

        VelocityControllerMessage msg;
        msg.v_vertical = 10.0;
        msg.v_horizontal = 20.0;
        msg.v_fwd = -0.01;
        msg.thetadot_horizontal = 0.023;
        msg.thetadot_vertical = -0.497;
        msg.btnA = false;
        msg.btnB = true;
        msg.btnX = false;
        msg.btnY = true;

        std::cout << msg << std::endl;

        std::ostringstream ssout;
        ssout << msg;
        std::cout << ssout.str() << std::endl;

        //char* msg_as_char = static_cast<char*>(static_cast<void*>(&msg));

        //char* msg_as_char = reinterpret_cast<char*>(&msg);
        std::string send_buf(ssout.str());
        socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
        std::cout << "Sent the message" << std::endl;

        //socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


	return 0;
}
