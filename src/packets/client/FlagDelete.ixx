module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:flagdelete;

import graal.packet;


export namespace graal::packet::client
{

// [STRING flag]

class FlagDelete : protected Packet
{
public:
	FlagDelete(packet::PacketData&& packet)
	{}

	FlagDelete(FlagDelete&& other) noexcept
	{}

	~FlagDelete() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::FLAGDELETE;
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
