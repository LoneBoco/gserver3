module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:hitobjects;

import graal.packet;


export namespace graal::packet::client
{

// [S1 power float][S1 x float][S1 y float] : ([U3 npcId] optional)

class HitObjects : protected Packet
{
public:
	HitObjects(packet::PacketData&& packet)
	{}

	HitObjects(HitObjects&& other) noexcept
	{}

	~HitObjects() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::HITOBJECTS;
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
