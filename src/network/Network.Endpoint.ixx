module;

#ifdef _WIN32
	#include <SDKDDKVer.h>
	#include <boost/asio.hpp>
#else
	#include <boost/asio.hpp>
#endif

#include "common.h"
#include <queue>
#include <variant>

export module graal.network:endpoint;

import graal.core;
import graal.packet;


using namespace boost;

export namespace graal::network
{

class NetworkEndpoint
{
public:
	NetworkEndpoint(asio::ip::tcp::socket&& socket)
		: m_socket(std::move(socket))
	{
	}

	~NetworkEndpoint() = default;

	NetworkEndpoint(const NetworkEndpoint& other) = delete;

	NetworkEndpoint(NetworkEndpoint&& other) noexcept
		: m_socket(std::move(other.m_socket))
	{
	}

	NetworkEndpoint& operator=(const NetworkEndpoint& other) = delete;
	NetworkEndpoint& operator=(NetworkEndpoint&& other) = delete;
	bool operator==(const NetworkEndpoint& other) = delete;

public:
	void Send(std::unique_ptr<graal::packet::Packet>&& packet)
	{
		std::visit([this, &packet](auto&& type)
		{
			using T = std::decay_t<decltype(type)>;
			if constexpr (std::is_same_v<T, graal::packet::ClientPacket>)
			{
				//Log::PrintLine("** Packet being sent to the client is not a server packet!");
				return;
			}
			else if constexpr (std::is_same_v<T, graal::packet::ServerPacket>)
			{
				switch (type)
				{
					case graal::packet::ServerPacket::LARGEFILESTART:
					case graal::packet::ServerPacket::LARGEFILEEND:
					case graal::packet::ServerPacket::LARGEFILESIZE:
						m_output_file.push(std::move(packet));
						break;
					default:
						m_output.push(std::move(packet));
						break;
				}
			}
			else
			{
				static_assert(std::false_type, "NetworkEndpoint::Send - Unable to handle packet.");
			}
		}, packet->Type());
	}

protected:
	asio::ip::tcp::socket m_socket;

	std::queue<graal::packet::PacketPtr> m_output;
	std::queue<graal::packet::PacketPtr> m_output_file;
};

using NetworkEndpointPtr = std::unique_ptr<NetworkEndpoint>;

} // end namespace graal::network
