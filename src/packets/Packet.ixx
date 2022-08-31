module;

#include "common.h"
#include <variant>

export module graal.packet;
export import :utilities;
export import :types;


import graal.core.versions;

/*
import std.core;
import std.memory;
*/


export namespace graal::packet
{

/*
class PacketData
{
public:
	PacketData(const std::vector<uint8_t>& data)
		: m_data(data)
	{}

	PacketData(std::vector<uint8_t>&& data) noexcept
		: m_data(std::move(data))
	{}

	~PacketData() = default;

public:
	operator std::vector<uint8_t>()
	{
		return m_data;
	}

public:
	using iterator = std::vector<uint8_t>::iterator;
	using const_iterator = std::vector<uint8_t>::const_iterator;

private:
	std::vector<uint8_t> m_data;
	size_t m_read_location = 0;
};
*/

using PacketData = std::vector<uint8_t>;
using PacketDataCIter = PacketData::const_iterator;
using PacketDataIter = PacketData::iterator;
using PacketIterRange = std::pair<PacketDataCIter, PacketDataCIter>;
using PacketType = std::variant<graal::packet::ClientPacket, graal::packet::ServerPacket>;

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
	virtual void SetVersion(graal::versions::Client version) {};

public:
	virtual PacketType Type() const = 0;
	virtual operator PacketData() const = 0;
};

using PacketPtr = std::unique_ptr<Packet>;

} // end namespace graal::packet
