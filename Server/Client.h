#ifndef CLIENT_H
#define CLIENT_H

#include <asio.hpp>

/**
 * @brief The Client class takes care of one connected client.
 */
class Client
{
public:
	Client( asio::ip::tcp::socket&& socket );

	void start( unsigned int serverStatus, std::function<void(Client*)> onDisconnect );

private:
	asio::ip::tcp::socket m_socket;
	std::function<void(Client*)> m_onDisconnect;

	asio::streambuf m_buffer;
};

#endif // CLIENT_H
