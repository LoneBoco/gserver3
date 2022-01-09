export module graal.level.parts:board;

import "common.h";

import graal.core;


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
