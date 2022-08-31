module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:itemtake;

import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y]

class ItemTake : protected Packet
{
public:
	ItemTake(packet::PacketData&& packet)
	{}

	ItemTake(ItemTake&& other) noexcept
	{}

	~ItemTake() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::ITEMTAKE;
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
