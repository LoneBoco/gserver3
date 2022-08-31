module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:updatescript;

import graal.packet;


export namespace graal::packet::client
{

// [STRING weapon]

class UpdateScript : protected Packet
{
public:
	UpdateScript(packet::PacketData&& packet)
	{}

	UpdateScript(UpdateScript&& other) noexcept
	{}

	~UpdateScript() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::UPDATESCRIPT;
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
