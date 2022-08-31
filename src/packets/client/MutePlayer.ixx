module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:muteplayer;

import graal.packet;


export namespace graal::packet::client
{

// [U2 playerId][U1 mute]
// mute: 0 off, 1 on

class MutePlayer : protected Packet
{
public:
	MutePlayer(packet::PacketData&& packet)
	{}

	MutePlayer(MutePlayer&& other) noexcept
	{}

	~MutePlayer() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::MUTEPLAYER;
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
