module;

#include "common.h"
#include "namespace.chrono.h"

export module graal.level.parts:board;

import graal.core;

/*
import std.core;

#include "namespace.chrono.h"
*/


export namespace graal::level
{

struct BoardChange
{
	Position2di Position;
	Size2Di Size;
	chrono::time_point LastUpdated;
	// tiles
};

} // end namespace graal::level
