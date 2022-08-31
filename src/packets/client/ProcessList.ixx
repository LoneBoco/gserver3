module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:processlist;

import graal.packet;


export namespace graal::packet::client
{

// [STRING processes csv]

class ProcessList : protected Packet
{
public:
	ProcessList(packet::PacketData&& packet)
	{}

	ProcessList(ProcessList&& other) noexcept
	{}

	~ProcessList() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::PROCESSLIST;
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
