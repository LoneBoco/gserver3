module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:npcadd;

import graal.packet;


export namespace graal::packet::client
{

// [GSTRING image][GSTRING code][S1 x float][S1 y float]

// PutNPC
class NPCAdd : protected Packet
{
public:
	NPCAdd(packet::PacketData&& packet)
	{}

	NPCAdd(NPCAdd&& other) noexcept
	{}

	~NPCAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::NPCADD;
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
