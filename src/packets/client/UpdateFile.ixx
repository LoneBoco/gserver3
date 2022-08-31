module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:updatefile;

import graal.packet;


export namespace graal::packet::client
{

// [U5 modTime][STRING file]

class UpdateFile : protected Packet
{
public:
	UpdateFile(packet::PacketData&& packet)
	{}

	UpdateFile(UpdateFile&& other) noexcept
	{}

	~UpdateFile() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::UPDATEFILE;
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
