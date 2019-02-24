#include "Client.h"

#include <iostream>

Client::Client(asio::ip::tcp::socket&& socket )
    : m_socket( std::move(socket) ) // move the socket from the Server object here so that it's free in the server
{

}

/**
 * @brief Client::start Starts the conversation with the client.
 * @param serverStatus The server status to send to the client.
 * @param onDisconnect A callback for when the client disconnected.
 */
void Client::start(unsigned int serverStatus, std::function<void(Client*)> onDisconnect)
{
	m_onDisconnect = onDisconnect;

	// read some data from the clinet
	asio::error_code errorCode;
	std::array<char, 128> buffer;
	size_t messageLength = m_socket.read_some(asio::buffer(buffer), errorCode);

	// check for any errors while receiving
	if( errorCode )
	{
		std::cout << "ASIO error: " << errorCode.message() << std::endl;
		return;
	}

	// and display it
	std::cout.write(buffer.data(), messageLength);


	// now send a status message to the client
	std::string message = std::to_string( serverStatus ) + "\n";
	asio::write(m_socket, asio::buffer(message), errorCode);

	// check for any errors while sending
	if( errorCode )
	{
		std::cout << "ASIO error: " << errorCode.message() << std::endl;
		return;
	}

	m_onDisconnect(this);
}
