module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:messagetoall;

import graal.packet;


export namespace graal::packet::client
{

// [GSTRING message]

class MessageToAll : protected Packet
{
public:
	MessageToAll(packet::PacketData&& packet)
	{}

	MessageToAll(MessageToAll&& other) noexcept
	{}

	~MessageToAll() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::MESSAGETOALL;
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
