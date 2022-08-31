module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:updatepackage;

import graal.packet;


export namespace graal::packet::client
{

// [GSTRING package][U1 installType] ([U5 checksum] repeated)

class UpdatePackage : protected Packet
{
public:
	UpdatePackage(packet::PacketData&& packet)
	{}

	UpdatePackage(UpdatePackage&& other) noexcept
	{}

	~UpdatePackage() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::UPDATEPACKAGE;
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
