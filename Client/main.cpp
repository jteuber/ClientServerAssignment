#include <iostream>

#include <asio.hpp>

// CLIENT
int main()
{
	try
	{
		// Connect and give it some time to connect
		asio::ip::tcp::iostream stream("localhost", "12345");
		stream.expires_from_now(std::chrono::seconds(60));

		// Send the message
		stream << "Hello World!\r\n";

		// and then receive the confirmation
		std::string status;
		while( std::getline(stream, status) )
			std::cout << status << "\n";
		std::cout << stream.rdbuf();

		// check for any errors
		if( !stream )
		{
			std::cout << "Socket error: " << stream.error().message() << std::endl;
			return 1;
		}

		// we don't need to close the stream explicitly as that is done by the destructor when it's going out if scope
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
