module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:npcprops;

import graal.packet;


export namespace graal::packet::client
{

// [U3 npcId] ([U1 prop][...] repeated)

class NPCProps : protected Packet
{
public:
	NPCProps(packet::PacketData&& packet)
	{}

	NPCProps(NPCProps&& other) noexcept
	{}

	~NPCProps() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::NPCPROPS;
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
