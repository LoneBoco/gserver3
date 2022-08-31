module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:npcdelete;

import graal.packet;


export namespace graal::packet::client
{

// [U3 npcId]

class NPCDelete : protected Packet
{
public:
	NPCDelete(packet::PacketData&& packet)
	{}

	NPCDelete(NPCDelete&& other) noexcept
	{}

	~NPCDelete() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::NPCDELETE;
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
