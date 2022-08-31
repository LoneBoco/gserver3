module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:explosion;

import graal.core;
import graal.packet;


export namespace graal::packet::client
{

// [U1 radius][S1 x float][S1 y float][U1 power]

class Explosion : protected Packet
{
public:
	Explosion(packet::PacketData&& packet)
	{
		int8_t x;
		int8_t y;

		packet >> packet::ReadGraalByte<1>(Radius)
			>> packet::ReadGraalByte<1>(x) >> packet::ReadGraalByte<1>(y)
			>> packet::ReadGraalByte<1>(Power);

		Location.X = static_cast<float>(x) / 2.0f;
		Location.Y = static_cast<float>(y) / 2.0f;
	}

	Explosion(Explosion&& other) noexcept
		: Radius(other.Radius), Location(other.Location), Power(other.Power)
	{}

	~Explosion() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::EXPLOSION;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	uint8_t Radius;
	Position2Df Location;
	uint8_t Power;
};

} // end namespace graal::packet::client
