module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:bombadd;

import graal.core;
import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y][U1 player_power ?][U1 duration]
// player_power: player = player_power >> 2
//               power = player_power & 0x03
// duration: units of 0.05 seconds
//           default = 55 (2.75 seconds)

class BombAdd : protected Packet
{
public:
	BombAdd(packet::PacketData&& packet)
	{
		uint8_t player_power;

		packet >> packet::ReadGraalFloat<1>(Location.X) >> packet::ReadGraalFloat<1>(Location.Y)
			>> packet::ReadGraalByte<1>(player_power) >> packet::ReadGraalByte<1>(Duration);

		//packet >> packet::ReadGraalFloat<1>(Location.X);
		//packet >> packet::ReadGraalFloat<1>(Location.Y);
		//packet >> packet::ReadGraalByte<1>(player_power);
		//packet >> packet::ReadGraalByte<1>(Duration);

		Player = player_power >> 2;
		Power = player_power & 0x03;
	}

	BombAdd(BombAdd&& other) noexcept
		: Location(other.Location), Player(other.Player), Power(other.Power), Duration(other.Duration)
	{}

	~BombAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::BOMBADD;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	std::chrono::milliseconds DurationInMilliseconds()
	{
		return 50ms * Duration;
	}

public:
	Position2Df Location;
	uint8_t Player;
	uint8_t Power;
	uint8_t Duration;
};

} // end namespace graal::packet::client
