export module graal.packet;
export import :utilities;

//export import graal.packet.types;

import graal.core;

import "common.h";
import <array>;


export namespace graal::packet
{

using PacketData = std::vector<uint8_t>;

struct Packet
{
public:
	Packet() = default;
	virtual ~Packet() {}

	Packet(const Packet& other) = delete;
	Packet(Packet&& other) = delete;
	Packet& operator=(const Packet& other) = delete;
	Packet& operator=(Packet&& other) = delete;
	bool operator==(const Packet& other) = delete;

public:
	virtual operator PacketData() const = 0;
};

} // end namespace graal::packet
