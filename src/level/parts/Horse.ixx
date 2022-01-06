export module graal.level.parts:horse;

import "common.h";

import graal.core;


export namespace graal::level
{

struct Horse
{
	core::Position2df Position;
	int8_t Direction;
	uint8_t Bushes;
	std::string Image;
	// timeout
};

} // end namespace graal::level