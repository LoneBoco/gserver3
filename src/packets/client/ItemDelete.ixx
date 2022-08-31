module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:itemdelete;

import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y]

class ItemDelete : protected Packet
{
public:
	ItemDelete(packet::PacketData&& packet)
	{}

	ItemDelete(ItemDelete&& other) noexcept
	{}

	~ItemDelete() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::ITEMDELETE;
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
