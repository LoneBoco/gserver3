module;

#include "common.h"

export module graal.level.parts:chest;

import graal.core;


export namespace graal::level
{

struct Chest
{
	Position2di Position;
	uint8_t Item;
	uint8_t Sign;
};

} // end namespace graal::level
