module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:sendtext;

import graal.packet;


export namespace graal::packet::client
{

// [STRING request csv]

class SendText : protected Packet
{
public:
	SendText(packet::PacketData&& packet)
	{}

	SendText(SendText&& other) noexcept
	{}

	~SendText() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::SENDTEXT;
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
