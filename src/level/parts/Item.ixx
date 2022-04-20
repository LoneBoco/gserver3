module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.level.parts:item;

import graal.core;

/*
import std.core;

#include "namespace.chrono.h"
*/


export namespace graal::level
{

struct Item
{
	Position2df Position;
	int8_t Item;
	chrono::time_point LastUpdated;
	// timeout
};

} // end namespace graal::level
