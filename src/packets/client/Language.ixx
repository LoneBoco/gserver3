module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:language;

import graal.packet;


export namespace graal::packet::client
{

// [STRING language]

class Language : protected Packet
{
public:
	Language(packet::PacketData&& packet)
	{}

	Language(Language&& other) noexcept
	{}

	~Language() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::LANGUAGE;
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
