export module graal.packet.types.client:levelwarp;

import "common.h";
import graal.packet;


export namespace graal::packet::client
{

// [UBYTE5 modtime][SBYTE1 x (float)][SBYTE1 y (float)][STRING level]
class LevelWarp : protected Packet
{
public:
	LevelWarp(const chrono::file_time& mod, const float x, const float y, const std::string& level)
		: ModificationTime(mod), X(x), Y(y), Level(level)
	{}

	LevelWarp(const packet::PacketData&& packet)
	{
		// TODO.
	}

	~LevelWarp() override {}

public:
	operator packet::PacketData() const override
	{
		packet::PacketData result;
		result << packet::GRAALBYTE<5>(static_cast<uint64_t>(ModificationTime.time_since_epoch().count()))
			<< packet::GRAALBYTE<1>(static_cast<uint64_t>(X * 2))
			<< packet::GRAALBYTE<1>(static_cast<uint64_t>(Y * 2))
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
