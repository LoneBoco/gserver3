export module graal.level.parts:board;

import "common.h";

import graal.core;


export namespace graal::level
{

struct BoardChange
{
	core::Position2di Position;
	core::Size2Di Size;
	chrono::time_point LastUpdated;
	// tiles
};

} // end namespace graal::level
