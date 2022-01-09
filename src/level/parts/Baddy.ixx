export module graal.level.parts:baddy;

import "common.h";

import graal.core;
import graal.packet;


export namespace graal::level
{

enum class BaddyProp
{
	ID = 0,
	X = 1,
	Y = 2,
	TYPE = 3,
	POWERIMAGE = 4,
	MODE = 5,
	ANI = 6,
	DIR = 7,
	VERSESIGHT = 8,
	VERSEHURT = 9,
	VERSEATTACK = 10,
	COUNT
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
