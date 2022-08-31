module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:openchest;

import graal.packet;


export namespace graal::packet::client
{

// [U1 x][U1 y]

class OpenChest : protected Packet
{
public:
	OpenChest(packet::PacketData&& packet)
	{}

	OpenChest(OpenChest&& other) noexcept
	{}

	~OpenChest() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::OPENCHEST;
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
