#include <iostream>

#include <asio.hpp>

#include "TcpServer.h"

// SERVER
int main()
{
	try
	{
		// Use the TcpServer class to take care of the event loop and accepting clients
		TcpServer server(12345);
		server.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
