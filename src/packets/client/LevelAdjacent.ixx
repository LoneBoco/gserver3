module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:leveladjacent;

import graal.packet;


export namespace graal::packet::client
{

// [U5 modTime][STRING level]

class LevelAdjacent : protected Packet
{
public:
	LevelAdjacent(packet::PacketData&& packet)
	{}

	LevelAdjacent(LevelAdjacent&& other) noexcept
	{}

	~LevelAdjacent() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::LEVELADJACENT;
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
