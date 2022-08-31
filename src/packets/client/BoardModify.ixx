module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:boardmodify;

import graal.core;
import graal.packet;


export namespace graal::packet::client
{

// [S1 x][S1 y][U1 width][U1 height][U2 tiles...]

class BoardModify : protected Packet
{
public:
	BoardModify(packet::PacketData&& packet)
	{
		packet >> packet::ReadGraalByte<1>(Location.X) >> packet::ReadGraalByte<1>(Location.Y)
			>> packet::ReadGraalByte<1>(Dimension.Width) >> packet::ReadGraalByte<1>(Dimension.Height);

		// TODO: All the tiles.
	}

	BoardModify(BoardModify&& other) noexcept
		: Location(std::move(other.Location)), Dimension(std::move(other.Dimension)), Tiles(std::move(other.Tiles))
	{}

	~BoardModify() override {}

public:
	packet::PacketType Type() const override
	{
		return graal::packet::ClientPacket::BOARDMODIFY;
	}

public:
	operator packet::PacketData() const override
	{
		//static_assert(false, "Trying to write packet from client.  Write the server variant instead.");
		return {};
	}

	//operator packet::PacketData() const override
	//{
	//	packet::PacketData result;
	//	result << packet::WriteGraalByte<1>(Location.X) << packet::WriteGraalByte<1>(Location.Y)
	//		<< packet::WriteGraalByte<1>(Dimension.Width) << packet::WriteGraalByte<1>(Dimension.Height);

	//	std::for_each(std::begin(Tiles), std::end(Tiles), [&result](const auto& tile) { result << packet.WriteGraalByte<2>(tile); });
	//	return result;
	//}

public:
	Position2Di Location;
	Size2Di Dimension;
	std::vector<uint16_t> Tiles;
};

} // end namespace graal::packet::client
