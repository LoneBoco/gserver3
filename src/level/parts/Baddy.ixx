module;

#include "common.h"

export module graal.level.parts:baddy;

import graal.core;
import graal.packet;


export namespace graal::level
{

enum class BaddyProp
{
	ID = 0,
	X,
	Y,
	TYPE,
	POWERIMAGE,
	MODE,
	ANI,
	DIR,
	VERSESIGHT,
	VERSEHURT,
	VERSEATTACK,

	COUNT
};

enum class BaddyMode
{
	WALK = 0,
	LOOK,
	HUNT,
	HURT,
	BUMPED,
	DIE,
	SWAMPSHOT,
	HAREJUMP,
	OCTOSHOT,
	DEAD,

	COUNT
};

struct BaddyData
{
	std::string Image;
	BaddyMode StartMode;
	uint8_t StartPower;
};

const int BaddyTypeCount = 10;
const std::array<BaddyData, BaddyTypeCount> BaddyInfo = {
	  BaddyData { "baddygray.png",     BaddyMode::WALK, 2 }
	, BaddyData { "baddyblue.png",     BaddyMode::WALK, 3 }
	, BaddyData { "baddyred.png",      BaddyMode::WALK, 4 }
	, BaddyData { "baddyblue.png",     BaddyMode::WALK, 3 }
	, BaddyData { "baddygray.png",     BaddyMode::SWAMPSHOT, 2 }
	, BaddyData { "baddyhare.png",     BaddyMode::HAREJUMP, 1 }
	, BaddyData { "baddyoctopus.png",  BaddyMode::WALK, 1 }
	, BaddyData { "baddygold.png",     BaddyMode::WALK, 6 }
	, BaddyData { "baddylizardon.png", BaddyMode::WALK, 12 }
	, BaddyData { "baddydragon.png",   BaddyMode::WALK, 8 }
};


struct Baddy
{
	ObjectProperties Properties = {
		  { ENUMID(BaddyProp::ID), PropertyType::UNSIGNED, props::in::GraalByte1, props::out::GraalByte1 }
		, { ENUMID(BaddyProp::X), PropertyType::FLOAT, props::in::FloatPosition, props::out::FloatPosition }
		, { ENUMID(BaddyProp::Y), PropertyType::FLOAT, props::in::FloatPosition, props::out::FloatPosition }
		, { ENUMID(BaddyProp::TYPE), PropertyType::FLOAT, props::in::GraalByte1, props::out::GraalByte1 }
		, { ENUMID(BaddyProp::POWERIMAGE), { PropertyType::FLOAT, PropertyType::STRING },
				[](const packet::PacketData& data, Property& prop) -> std::size_t { return 0; },
				[](const PropertyGroup& prop) -> packet::PacketData {
					packet::PacketData result;
					result << props::out::GraalByte<1>(prop[0]) << props::out::ClassicString<1>(prop[1]);
					//result << packet::WriteGraalByte<1>(prop[0].GetUnsigned()) << packet::WriteClassicString<1>(prop[1].GetString());
					return result;
				}
			}
		, { ENUMID(BaddyProp::MODE), PropertyType::UNSIGNED, props::in::GraalByte1, props::out::GraalByte1 }
		, { ENUMID(BaddyProp::ANI), PropertyType::UNSIGNED, props::in::GraalByte1, props::out::GraalByte1 }
		, { ENUMID(BaddyProp::DIR), PropertyType::UNSIGNED, props::in::GraalByte1, props::out::GraalByte1 }
		, { ENUMID(BaddyProp::MODE), PropertyType::UNSIGNED, props::in::GraalByte1, props::out::GraalByte1 }
		, { ENUMID(BaddyProp::VERSESIGHT), PropertyType::STRING, props::in::ClassicString1, props::out::ClassicString1 }
		, { ENUMID(BaddyProp::VERSEHURT), PropertyType::STRING, props::in::ClassicString1, props::out::ClassicString1 }
		, { ENUMID(BaddyProp::VERSEATTACK), PropertyType::STRING, props::in::ClassicString1, props::out::ClassicString1 }
	};

	bool CanRespawn = true;
};

} // end namespace graal::level
