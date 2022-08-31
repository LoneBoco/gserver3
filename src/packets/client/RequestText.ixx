module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:requesttext;

import graal.packet;


export namespace graal::packet::client
{

// [STRING request csv]

class RequestText : protected Packet
{
public:
	RequestText(packet::PacketData&& packet)
	{}

	RequestText(RequestText&& other) noexcept
	{}

	~RequestText() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::REQUESTTEXT;
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
