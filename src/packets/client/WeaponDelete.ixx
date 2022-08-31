module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:weapondelete;

import graal.packet;


export namespace graal::packet::client
{

// [STRING weapon]

class WeaponDelete : protected Packet
{
public:
	WeaponDelete(packet::PacketData&& packet)
	{}

	WeaponDelete(WeaponDelete&& other) noexcept
	{}

	~WeaponDelete() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::WEAPONDELETE;
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
