#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <list>

#include <asio.hpp>

#include "Client.h"

/**
 * @brief The TcpServer keeps listening for new clients asynchronously and creates a Client object for each client.
 */
class TcpServer
{
public:
	TcpServer( unsigned short port );

	void run();

private:
	void clientConnected(const asio::error_code& error, asio::ip::tcp::socket&& socket );

private:
	unsigned int m_status;

	asio::io_context m_ioContext;
	asio::ip::tcp::acceptor m_acceptor;

	std::list<Client> m_clientList;
};

#endif // TCPSERVER_H
