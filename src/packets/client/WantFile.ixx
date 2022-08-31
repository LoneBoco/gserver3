module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:wantfile;

import graal.packet;


export namespace graal::packet::client
{

// [STRING file]

class WantFile : protected Packet
{
public:
	WantFile(packet::PacketData&& packet)
	{}

	WantFile(WantFile&& other) noexcept
	{}

	~WantFile() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::WANTFILE;
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
