#include "Client.h"

#include <iostream>

Client::Client(asio::ip::tcp::socket&& socket )
    : m_socket( std::move(socket) ) // move the socket from the Server object here so that it's free in the server
    , m_buffer( 100 )
{}

/**
 * @brief Client::start Starts the conversation with the client.
 * @param serverStatus The server status to send to the client.
 * @param onDisconnect A callback for when the client disconnected.
 */
void Client::start(unsigned int serverStatus, std::function<void(Client*)> onDisconnect)
{
	m_onDisconnect = onDisconnect;

	// read some data from the client
	asio::async_read_until( m_socket, m_buffer, '\n',
	                          [serverStatus, this] (const asio::error_code& error, std::size_t /*bytesReceived*/)
	{
		// check for any errors while receiving
		if( error )
		{
			std::cout << "ASIO error: " << error.message() << std::endl;
			return;
		}

		// and display it
		std::cout << &m_buffer;
		std::cout.flush(); // just to be sure to stay up-to-date


		// now send a status message to the client
		std::string message = std::to_string( serverStatus ) + "\n";
		m_socket.async_write_some(asio::buffer(message), [this] (const asio::error_code& error, std::size_t) {
			// check for any errors while sending
			if( error )
			{
				std::cout << "ASIO error: " << error.message() << std::endl;
				return;
			}

			m_onDisconnect(this);
		} );
	} );
}
