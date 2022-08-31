module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:baddyprops;

import graal.packet;


export namespace graal::packet::client
{

// [U1 baddyId] ([U1 propId][...] repeated)

class BaddyProps : protected Packet
{
public:
	BaddyProps(packet::PacketData&& packet)
	{}

	BaddyProps(BaddyProps&& other) noexcept
	{}

	~BaddyProps() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::BADDYPROPS;
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
