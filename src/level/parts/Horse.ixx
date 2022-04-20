module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.level.parts:horse;

import graal.core;


export namespace graal::level
{

struct Horse
{
	Position2df Position;
	int8_t Direction;
	uint8_t Bushes;
	std::string Image;
	// timeout
};

} // end namespace graal::level
