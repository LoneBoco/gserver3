module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:updateclass;

import graal.packet;


export namespace graal::packet::client
{

// [U5 modTime][STRING class]

class UpdateClass : protected Packet
{
public:
	UpdateClass(packet::PacketData&& packet)
	{}

	UpdateClass(UpdateClass&& other) noexcept
	{}

	~UpdateClass() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::UPDATECLASS;
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
