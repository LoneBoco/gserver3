module;

#include "common.h"

export module graal.level.parts:sign;

import graal.core;


export namespace graal::level
{

struct Sign
{
	Position2di Position;
	std::string Text;
};

} // end namespace graal::level
