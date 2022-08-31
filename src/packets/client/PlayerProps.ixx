module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:playerprops;

import graal.packet;


export namespace graal::packet::client
{

// ([U1 propId][...] repeated)

class PlayerProps : protected Packet
{
public:
	PlayerProps(packet::PacketData&& packet)
	{}

	PlayerProps(PlayerProps&& other) noexcept
	{}

	~PlayerProps() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::PLAYERPROPS;
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
