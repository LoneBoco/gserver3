module;

#include "common.h"

export module graal.packet.types.server:levelboard;

import graal.packet;

//import std.core;


export namespace graal::packet::server
{

// [UBYTE5 modtime][SBYTE1 x (float)][SBYTE1 y (float)][STRING level]
class LevelBoard : protected Packet
{
public:
	LevelBoard()
	{}

	LevelBoard(LevelBoard&& other)
	{
		// TODO.
	}

	~LevelBoard() override {}

public:
	std::variant<graal::packet::ClientPacket, graal::packet::ServerPacket> Type() const override
	{
		return graal::packet::ServerPacket::LEVELBOARD;
	}

public:
	operator packet::PacketData() const override
	{
		packet::PacketData result;
		// Board changes.
		return result;
	}

public:
	// Board changes.
};

} // end namespace graal::packet::client
