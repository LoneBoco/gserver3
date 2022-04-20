module;

#include "common.h"
#include <variant>

export module graal.packet;
export import :utilities;
export import :types;


//import graal.core;

/*
import std.core;
import std.memory;
*/


export namespace graal::packet
{

using PacketData = std::vector<uint8_t>;
using PacketDataCIter = PacketData::const_iterator;
using PacketDataIter = PacketData::iterator;
using PacketIterRange = std::pair<PacketDataCIter, PacketDataCIter>;

struct Packet
{
public:
	Packet() = default;
	virtual ~Packet() {}

	Packet(const Packet& other) = delete;
	Packet(Packet&& other) = default;
	Packet& operator=(const Packet& other) = delete;
	Packet& operator=(Packet&& other) = delete;
	bool operator==(const Packet& other) = delete;

public:
	virtual std::variant<graal::packet::ClientPacket, graal::packet::ServerPacket> Type() const = 0;

public:
	virtual operator PacketData() const = 0;
};

using PacketPtr = std::unique_ptr<Packet>;

} // end namespace graal::packet
