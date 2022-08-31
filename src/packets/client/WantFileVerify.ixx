module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:wantfileverify;

import graal.packet;


export namespace graal::packet::client
{

// [U5 crc32Checksum][GSTRING filename]

class WantFileVerify : protected Packet
{
public:
	WantFileVerify(packet::PacketData&& packet)
	{}

	WantFileVerify(WantFileVerify&& other) noexcept
	{}

	~WantFileVerify() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::WANTFILEVERIFY;
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
