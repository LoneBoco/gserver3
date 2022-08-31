module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:profileset;

import graal.packet;


export namespace graal::packet::client
{

// [GSTRING account][GSTRING name][GSTRING age][GSTRING gender][GSTRING country][GSTRING messenger][GSTRING email][GSTRING website][GSTRING hangout][GSTRING quote]

class ProfileSet : protected Packet
{
public:
	ProfileSet(packet::PacketData&& packet)
	{}

	ProfileSet(ProfileSet&& other) noexcept
	{}

	~ProfileSet() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::PROFILESET;
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
