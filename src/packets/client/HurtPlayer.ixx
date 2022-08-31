module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:hurtplayer;

import graal.packet;


export namespace graal::packet::client
{

// [U2 playerId][S1 hurtdx][S1 hurtdy][U1 power][U3 npcId]

class HurtPlayer : protected Packet
{
public:
	HurtPlayer(packet::PacketData&& packet)
	{}

	HurtPlayer(HurtPlayer&& other) noexcept
	{}

	~HurtPlayer() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::HURTPLAYER;
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
