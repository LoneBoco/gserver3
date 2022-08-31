module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:claimpker;

import graal.packet;


export namespace graal::packet::client
{

// [U2 playerId]

class ClaimPKer : protected Packet
{
public:
	ClaimPKer(packet::PacketData&& packet)
	{
		packet >> packet::ReadGraalByte<2>(PlayerId);
	}

	ClaimPKer(ClaimPKer&& other) noexcept
		: PlayerId(other.PlayerId)
	{}

	~ClaimPKer() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::CLAIMPKER;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	uint16_t PlayerId;
};

} // end namespace graal::packet::client
