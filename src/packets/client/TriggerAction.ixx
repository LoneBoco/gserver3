module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:triggeraction;

import graal.packet;


export namespace graal::packet::client
{

// [U3 npcId][S1 x float][S1 y float][STRING action csv]

class TriggerAction : protected Packet
{
public:
	TriggerAction(packet::PacketData&& packet)
	{}

	TriggerAction(TriggerAction&& other) noexcept
	{}

	~TriggerAction() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::TRIGGERACTION;
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
