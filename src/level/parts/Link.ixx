export module graal.level.parts:link;

import "common.h";

import graal.core;


export namespace graal::level
{

struct Link
{
	Position2di Position;
	Size2Di Size;
	std::string DestinationLevel;
	std::string DestinationX;
	std::string DestinationY;
};

} // end namespace graal::level
