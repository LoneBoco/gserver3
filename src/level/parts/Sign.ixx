export module graal.level.parts:sign;

import "common.h";

import graal.core;


export namespace graal::level
{

struct Sign
{
	core::Position2di Position;
	std::string Text;
};

} // end namespace graal::level
