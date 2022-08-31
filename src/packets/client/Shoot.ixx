module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:shoot;

import graal.packet;


export namespace graal::packet::client
{

// [U3 unknown][S1 x float][S1 y float][S1 z float][U1 angle][U1 angleZ][U1 speed][GSTRING gani][U1 shootParamsLength][STRING shootParams]
// unknown: Seems to always be 0.
// angle:  0-pi maybe (0-220)
// angleZ: 0-pi maybe (0-220)
// speed: pixels per 0.05 seconds.  Each value of 1 translates to 44 pixels.
// gani: What about ganiParams?
// shootParamsLength: Number of shootparams, but the client doesn't limit itself and sends the overflow anyway.

class Shoot : protected Packet
{
public:
	Shoot(packet::PacketData&& packet)
	{}

	Shoot(Shoot&& other) noexcept
	{}

	~Shoot() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::SHOOT;
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
