module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:levelwarpmod;

import graal.packet;


export namespace graal::packet::client
{

// [U5 modtime][S1 x float][S1 y float][STRING level]

class LevelWarpMod : protected Packet
{
public:
	LevelWarpMod(packet::PacketData&& packet)
	{}

	LevelWarpMod(LevelWarpMod&& other) noexcept
	{}

	~LevelWarpMod() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::LEVELWARPMOD;
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
