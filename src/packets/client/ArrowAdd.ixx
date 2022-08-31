module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:arrowadd;

import graal.packet;


export namespace graal::packet::client
{

// ?

class ArrowAdd : protected Packet
{
public:
	ArrowAdd(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	ArrowAdd(ArrowAdd&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~ArrowAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::ARROWADD;
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
