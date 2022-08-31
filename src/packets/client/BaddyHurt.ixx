module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:baddyhurt;

import graal.packet;


export namespace graal::packet::client
{

// ?

class BaddyHurt : protected Packet
{
public:
	BaddyHurt(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	BaddyHurt(BaddyHurt&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~BaddyHurt() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::BADDYHURT;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	packet::PacketData Data;
};

} // end namespace graal::packet::client
