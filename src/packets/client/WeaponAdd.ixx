module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:weaponadd;

import graal.packet;


export namespace graal::packet::client
{

// [U1 type] |
// type 0: [U1 defaultWeapon]
// type 1: [U3 npcId]

class WeaponAdd : protected Packet
{
public:
	WeaponAdd(packet::PacketData&& packet)
	{}

	WeaponAdd(WeaponAdd&& other) noexcept
	{}

	~WeaponAdd() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::WEAPONADD;
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
