module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:showimage;

import graal.packet;


export namespace graal::packet::client
{

// ?

class ShowImage : protected Packet
{
public:
	ShowImage(packet::PacketData&& packet)
		: Data(std::move(packet))
	{}

	ShowImage(ShowImage&& other) noexcept
		: Data(std::move(other.Data))
	{}

	~ShowImage() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::SHOWIMAGE;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

public:
	packet::PacketData Data;
};

} // end namespace graal::packet::client
