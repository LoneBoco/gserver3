module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:flagset;

import graal.packet;


export namespace graal::packet::client
{

// [STRING flag]

class FlagSet : protected Packet
{
public:
	FlagSet(packet::PacketData&& packet)
	{}

	FlagSet(FlagSet&& other) noexcept
	{}

	~FlagSet() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::FLAGSET;
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
