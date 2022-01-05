export module graal.level.parts:chest;

import "common.h";

import graal.core;


export namespace graal::level
{

struct Chest
{
	core::Position2di Position;
	uint8_t Item;
	uint8_t Sign;
};

} // end namespace graal::level
