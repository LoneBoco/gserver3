module;

#include "common.h"

export module graal.core:colors;


namespace graal
{

static const char* colors[] =
{
	"white",
	"yellow",
	"orange",
	"pink",
	"red",
	"darkred",
	"lightgreen",
	"green",
	"darkgreen",
	"lightblue",
	"blue",
	"darkblue",
	"brown",
	"cynober",
	"purple",
	"darkpurple",
	"lightgray",
	"gray",
	"black",
	"transparent",
	0
};

export
enum class Color
{
	WHITE = 0,
	YELLOW,
	ORANGE,
	PINK,
	RED,
	DARKRED,
	LIGHTGREEN,
	GREEN,
	DARKGREEN,
	LIGHTBLUE,
	BLUE,
	DARKBLUE,
	BROWN,
	CYNOBER,
	PURPLE,
	DARKPURPLE,
	LIGHTGRAY,
	GRAY,
	BLACK,
	TRANSPARENT,

	INVALID
};

export
Color getColor(const std::string_view& color)
{
	int idx = 0;
	while (colors[idx] != 0)
	{
		if (boost::iequals(color, std::string_view{ colors[idx] }))
			break;

		++idx;
	}

	return static_cast<Color>(idx);
}

} // end namespace graal
