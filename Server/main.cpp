#include <iostream>

#include <asio.hpp>

#include "TcpServer.h"

// SERVER
int main()
{
	try
	{
		TcpServer server(12345);
		server.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
