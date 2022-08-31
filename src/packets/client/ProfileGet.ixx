module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:profileget;

import graal.packet;


export namespace graal::packet::client
{

// [STRING account]

class ProfileGet : protected Packet
{
public:
	ProfileGet(packet::PacketData&& packet)
	{}

	ProfileGet(ProfileGet&& other) noexcept
	{}

	~ProfileGet() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::PROFILEGET;
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
