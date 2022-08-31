module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:privatemessage;

import graal.packet;


export namespace graal::packet::client
{

// [U2 playerCount] ([U2 player] repeated on playerCount) [STRING message]

class PrivateMessage : protected Packet
{
public:
	PrivateMessage(packet::PacketData&& packet)
	{}

	PrivateMessage(PrivateMessage&& other) noexcept
	{}

	~PrivateMessage() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::PRIVATEMESSAGE;
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
