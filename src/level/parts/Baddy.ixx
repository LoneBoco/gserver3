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
	core::ObjectProperties Properties = {
		  { ENUMID(BaddyProp::ID), core::PropertyType::UNSIGNED, core::props::in::GraalByte1, core::props::out::GraalByte1 }
		, { ENUMID(BaddyProp::X), core::PropertyType::FLOAT, core::props::in::FloatPosition, core::props::out::FloatPosition }
		, { ENUMID(BaddyProp::Y), core::PropertyType::FLOAT, core::props::in::FloatPosition, core::props::out::FloatPosition }
		, { ENUMID(BaddyProp::TYPE), core::PropertyType::FLOAT, core::props::in::GraalByte1, core::props::out::GraalByte1 }
		, { ENUMID(BaddyProp::POWERIMAGE), { core::PropertyType::FLOAT, core::PropertyType::STRING },
				[](const packet::PacketData& data, core::Property& prop) -> std::size_t { return 0; },
				[](const core::PropertyGroup& prop) -> packet::PacketData {
					packet::PacketData result;
					result << core::props::out::GraalByte<1>(prop[0]) << core::props::out::ClassicString<1>(prop[1]);
					//result << packet::WriteGraalByte<1>(prop[0].GetUnsigned()) << packet::WriteClassicString<1>(prop[1].GetString());
					return result;
				}
			}
		, { ENUMID(BaddyProp::MODE), core::PropertyType::UNSIGNED, core::props::in::GraalByte1, core::props::out::GraalByte1 }
		, { ENUMID(BaddyProp::ANI), core::PropertyType::UNSIGNED, core::props::in::GraalByte1, core::props::out::GraalByte1 }
		, { ENUMID(BaddyProp::DIR), core::PropertyType::UNSIGNED, core::props::in::GraalByte1, core::props::out::GraalByte1 }
		, { ENUMID(BaddyProp::MODE), core::PropertyType::UNSIGNED, core::props::in::GraalByte1, core::props::out::GraalByte1 }
		, { ENUMID(BaddyProp::VERSESIGHT), core::PropertyType::STRING, core::props::in::ClassicString1, core::props::out::ClassicString1 }
		, { ENUMID(BaddyProp::VERSEHURT), core::PropertyType::STRING, core::props::in::ClassicString1, core::props::out::ClassicString1 }
		, { ENUMID(BaddyProp::VERSEATTACK), core::PropertyType::STRING, core::props::in::ClassicString1, core::props::out::ClassicString1 }
	};

	bool CanRespawn = true;
};

} // end namespace graal::level
