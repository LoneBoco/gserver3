module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.packet.types.client:levelwarp;

import graal.packet;

/*
import std.core;
import std.memory;

#include "namespace.chrono.h"
*/


export namespace graal::packet::client
{

// [UBYTE5 modtime][SBYTE1 x (float)][SBYTE1 y (float)][STRING level]
class LevelWarp : protected Packet
{
public:
	LevelWarp(const chrono::file_time& mod, const float x, const float y, const std::string& level)
		: ModificationTime(mod), X(x), Y(y), Level(level)
	{}

	LevelWarp(LevelWarp&& other)
		: ModificationTime(std::move(other.ModificationTime)), X(other.X), Y(other.Y), Level(std::move(other.Level))
	{
	}

	~LevelWarp() override {}

public:
	std::variant<graal::packet::ClientPacket, graal::packet::ServerPacket> Type() const override
	{
		return graal::packet::ClientPacket::LEVELWARP;
	}

public:
	operator packet::PacketData() const override
	{
		packet::PacketData result;
		result << packet::WriteGraalByte<5>(static_cast<uint64_t>(ModificationTime.time_since_epoch().count()))
			<< packet::WriteGraalByte<1>(static_cast<uint64_t>(X * 2))
			<< packet::WriteGraalByte<1>(static_cast<uint64_t>(Y * 2))
			<< Level;
		return result;
	}

public:
	chrono::file_time ModificationTime;
	float X;
	float Y;
	std::string Level;
};

} // end namespace graal::packet::client
