module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:firespy;

import graal.packet;


export namespace graal::packet::client
{

// ?

class FireSpy : protected Packet
{
public:
	FireSpy(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	FireSpy(FireSpy&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~FireSpy() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::FIRESPY;
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
