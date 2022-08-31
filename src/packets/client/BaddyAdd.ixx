module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:baddyadd;

import graal.core;
import graal.packet;
import graal.level.parts;


export namespace graal::packet::client
{

// [S1 x float][S1 y float][U1 type][U1 power][STRING image]

class BaddyAdd : protected Packet
{
public:
	BaddyAdd(packet::PacketData&& packet) noexcept
	{
		int8_t x;
		int8_t y;

		packet >> packet::ReadGraalByte<1>(x) >> packet::ReadGraalByte<1>(y)
			>> packet::ReadGraalByte<1>(BaddyType) >> packet::ReadGraalByte<1>(Power)
			>> packet::ReadString<0>(Image);

		Location.X = static_cast<float>(x) / 2.0f;
		Location.Y = static_cast<float>(y) / 2.0f;
	}

	BaddyAdd(BaddyAdd&& other) noexcept
		: Location(std::move(other.Location)), BaddyType(other.BaddyType), Power(other.Power), Image(std::move(other.Image))
	{}

	~BaddyAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::BADDYADD;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	Position2Df Location;
	uint8_t BaddyType;
	uint8_t Power;
	std::string Image;
};

} // end namespace graal::packet::client
