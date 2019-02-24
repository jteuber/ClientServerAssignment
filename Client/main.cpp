#include <iostream>

#include <asio.hpp>

// CLIENT
int main()
{
	try
	{
		// create the context and things necessary to connect
		asio::io_context ioContext;
		asio::ip::tcp::socket socket( ioContext );
		asio::ip::tcp::endpoint endpoint( asio::ip::address_v4::from_string("127.0.0.1"), 12345 );

		// create a buffer to hold the received server status in
		asio::streambuf buffer;

		socket.async_connect( endpoint, [&] (const asio::error_code& error)
		{
			// check for any errors while connecting
			if( error )
			{
				std::cout << "ASIO error: " << error.message() << std::endl;
				return;
			}

			// Send the message
			std::string message = "Hello World!\n";
			socket.async_write_some(asio::buffer(message), [&] (const asio::error_code& error, std::size_t)
			{
				// check for any errors while sending
				if( error )
				{
					std::cout << "ASIO error: " << error.message() << std::endl;
					return;
				}

				// and then receive the confirmation
				asio::async_read_until( socket, buffer, '\n',
				                          [&] (const asio::error_code& error, std::size_t /*bytesReceived*/)
				{
					// check for any errors while receiving
					if( error )
					{
						std::cout << "ASIO error: " << error.message() << std::endl;
						return;
					}

					// and display it
					std::cout << &buffer;
					std::cout.flush(); // just to be sure to stay up-to-date
				} );
			} );
		} );


		// let the context take care of the event loop while stuff is being sent and received
		ioContext.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
