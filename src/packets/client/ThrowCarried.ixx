module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:throwcarried;

import graal.packet;


export namespace graal::packet::client
{

// ?

class ThrowCarried : protected Packet
{
public:
	ThrowCarried(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	ThrowCarried(ThrowCarried&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~ThrowCarried() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::THROWCARRIED;
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
