#include "TcpServer.h"

#include <iostream>

TcpServer::TcpServer( unsigned short port )
    : m_status( 0 )
    , m_acceptor(m_ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port) )
{
}

/**
 * @brief Waits and listens for new clients indefinitely.
 */
void TcpServer::run()
{
	m_acceptor.async_accept( m_ioContext, std::bind<void>(&TcpServer::clientConnected, this,
	                                                      std::placeholders::_1, std::placeholders::_2) );

	m_ioContext.run();
}

/**
 * @brief Creates the client-object with the new socket.
 * @param error Error object in case there was an error while accepting a connection.
 * @param socket New socket on which the client is connected.
 */
void TcpServer::clientConnected(const asio::error_code& error, asio::ip::tcp::socket&& socket)
{
	if( !error )
	{
		// create a new client in the list
		m_clientList.emplace_back( std::move(socket) );

		// get an iterator for the added client
		auto it = --m_clientList.end();

		// start this client and make sure to delete it from the list once it disconnected
		it->start( m_status++, [this, it] (Client* client)
		{
			// check if the iterator is still valid and points to the correct client
			if( client == &(*it) )
				m_clientList.erase( it );
			// in production be careful to not delete an object from inside itself
		} );
	}
	else
	{
		std::cout << "ASIO error: " << error.message() << std::endl;
	}

	// accept the next client
	m_acceptor.async_accept( m_ioContext, std::bind<void>(&TcpServer::clientConnected, this,
	                                                      std::placeholders::_1, std::placeholders::_2) );
}
