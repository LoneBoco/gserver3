module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:packetcount;

import graal.packet;


export namespace graal::packet::client
{

// [U2 count]

class PacketCount : protected Packet
{
public:
	PacketCount(packet::PacketData&& packet)
	{}

	PacketCount(PacketCount&& other) noexcept
	{}

	~PacketCount() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::PACKETCOUNT;
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
