module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:bombdelete;

import graal.packet;


export namespace graal::packet::client
{

// ?

class BombDelete : protected Packet
{
public:
	BombDelete(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	BombDelete(BombDelete&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~BombDelete() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::BOMBDELETE;
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
