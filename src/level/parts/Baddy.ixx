export module graal.level.parts:baddy;

import "common.h";

import graal.core;


export namespace graal::level
{

struct Baddy
{
	core::Position2df Position;
	uint8_t Type;
	int8_t Power;
	int8_t Mode;
	uint8_t Animation;
	uint8_t Direction;
	std::string Image;
	std::vector<std::string> Verses;
	bool CanRespawn;

	// props
};

} // end namespace graal::level
