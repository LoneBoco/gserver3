module;

#include "common.h"

export module graal.player;

import graal.network;

//import std.core;
//import std.memory;


using namespace boost;

export namespace graal::player
{

class Player
{
public:
	Player(const uint16_t id, network::NetworkEndpointPtr&& endpoint)
		: m_id(id), m_endpoint(std::forward<network::NetworkEndpointPtr>(endpoint))
	{

	}

	~Player() = default;

	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;

	Player(Player&& other) noexcept
		: m_endpoint(std::move(other.m_endpoint))
	{
	}

	Player& operator=(Player&& other) noexcept
	{
		return *this;
	}

	bool operator==(const Player& other) const noexcept
	{
		return false;
	}

public:

protected:
	network::NetworkEndpointPtr m_endpoint;

	uint16_t m_id;
};

using PlayerPtr = std::shared_ptr<Player>;

} // end namespace graal::player
