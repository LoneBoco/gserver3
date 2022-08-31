module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:horseadd;

import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y][U1 dir_bush][STRING image]
// dir_bush: dir = dir_bush & 0x03
//           bush = dir_bush >> 2

class HorseAdd : protected Packet
{
public:
	HorseAdd(packet::PacketData&& packet)
	{}

	HorseAdd(HorseAdd&& other) noexcept
	{}

	~HorseAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::HORSEADD;
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
