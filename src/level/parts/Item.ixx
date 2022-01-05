export module graal.level.parts:item;

import "common.h";

import graal.core;


export namespace graal::level
{

struct Item
{
	core::Position2df Position;
	int8_t Item;
	chrono::time_point LastUpdated;
	// timeout
};

} // end namespace graal::level
