module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:horsedelete;

import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y]

class HorseDelete : protected Packet
{
public:
	HorseDelete(packet::PacketData&& packet)
	{}

	HorseDelete(HorseDelete&& other) noexcept
	{}

	~HorseDelete() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::HORSEDELETE;
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
