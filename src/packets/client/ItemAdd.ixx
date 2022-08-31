module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:itemadd;

import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y][U1 item]

class ItemAdd : protected Packet
{
public:
	ItemAdd(packet::PacketData&& packet)
	{}

	ItemAdd(ItemAdd&& other) noexcept
	{}

	~ItemAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::ITEMADD;
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
