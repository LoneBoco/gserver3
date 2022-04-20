module;

#include "common.h"

#ifdef _WIN32
	#include <SDKDDKVer.h>
	#include <boost/asio.hpp>
#else
	#include <boost/asio.hpp>
#endif

export module graal.network;
export import :endpoint;

//import graal.player;

//import std.core;
//import std.memory;


using namespace boost;

export namespace graal::network
{

typedef std::function<void(NetworkEndpointPtr&&)> player_connect_cb;


class Network
{
public:
	Network()
	{
	}

	~Network() = default;

	Network(const Network& other) = delete;
	Network(Network&& other) = delete;
	Network& operator=(const Network& other) = delete;
	Network& operator=(Network&& other) = delete;
	bool operator==(const Network& other) = delete;

public:
	void BindPlayerConnectCallback(player_connect_cb callback)
	{
		m_connect_cb = callback;
	}

	void Initialize(const uint16_t port)
	{
		m_endpoint = std::make_unique<asio::ip::tcp::endpoint>(asio::ip::tcp::v4(), port);
		m_acceptor = std::make_unique<asio::ip::tcp::acceptor>(m_context, *m_endpoint);

		m_acceptor->async_accept(std::bind(&Network::accept_player, this, std::placeholders::_1, std::placeholders::_2));
	}

public:
	void Run()
	{
		m_context.run();
	}

protected:
	void accept_player(const boost::system::error_code& ec, asio::ip::tcp::socket socket)
	{
		if (ec) return;
		assert(m_connect_cb != nullptr);

		if (m_connect_cb)
		{
			auto endpoint = std::make_unique<NetworkEndpoint>(std::move(socket));
			m_connect_cb(std::move(endpoint));
		}
	}

protected:
	player_connect_cb m_connect_cb;
	asio::io_context m_context;
	std::unique_ptr<asio::ip::tcp::endpoint> m_endpoint;
	std::unique_ptr<asio::ip::tcp::acceptor> m_acceptor;
};

} // end namespace graal::network
