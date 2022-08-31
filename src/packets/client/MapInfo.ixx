module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:mapinfo;

import graal.packet;


export namespace graal::packet::client
{

// ?

class MapInfo : protected Packet
{
public:
	MapInfo(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	MapInfo(MapInfo&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~MapInfo() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::MAPINFO;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	packet::PacketData Data;
};

} // end namespace graal::packet::client
