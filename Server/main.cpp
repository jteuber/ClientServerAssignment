#include <iostream>

#include <asio.hpp>

// SERVER
int main()
{
	try
	{
		// create the context and socket as well as an acceptor on which we will be accepting incoming connections
		asio::io_context ioContext;
		asio::ip::tcp::acceptor acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345));
		asio::ip::tcp::socket socket(ioContext);

		// block until we get a connection
		acceptor.accept(socket);

		// read some data from the clinet
		asio::error_code errorCode;
		std::array<char, 128> buffer;
		size_t messageLength = socket.read_some(asio::buffer(buffer), errorCode);

		// check for any errors while receiving
		if( errorCode )
		{
			std::cout << "ASIO error: " << errorCode.message() << std::endl;
			return 1;
		}

		// and display it
		std::cout.write(buffer.data(), messageLength);


		// now send a status message to the client
		std::string message = "ack\n";
		asio::write(socket, asio::buffer(message), errorCode);

		// check for any errors while sending
		if( errorCode )
		{
			std::cout << "ASIO error: " << errorCode.message() << std::endl;
			return 1;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
