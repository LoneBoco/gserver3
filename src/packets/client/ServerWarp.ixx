module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:serverwarp;

import graal.packet;


export namespace graal::packet::client
{

// [STRING server]

class ServerWarp : protected Packet
{
public:
	ServerWarp(packet::PacketData&& packet)
	{}

	ServerWarp(ServerWarp&& other) noexcept
	{}

	~ServerWarp() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::SERVERWARP;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
};

} // end namespace graal::packet::client
