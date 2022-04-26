module;

#include <cstdint>

export module graal.core;

export import :base64;
export import :colors;
export import :concepts;
export import :flags;
export import :log;
export import :position;
export import :props;
export import :random;
export import :ranges;
export import :utilities;
export import graal.core.events;

//import std.core;


export namespace graal
{

uint16_t ENUMID(auto e)
{
	return static_cast<uint16_t>(e);
}

}
