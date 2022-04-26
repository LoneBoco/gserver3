module;

#include "common.h"

export module graal.core.versions:client;
import :base;


export namespace graal::versions
{

enum class Client
{
	VER_UNKNOWN,
	VER_NPCSERVER,
	VER_1_25,
	VER_1_27,
	VER_1_28,
	VER_1_31,
	VER_1_32,
	VER_1_322,
	VER_1_323,
	VER_1_324,
	VER_1_33,
	VER_1_331,
	VER_1_34,
	VER_1_341,
	VER_1_35,
	VER_1_36,
	VER_1_37,
	VER_1_371,
	VER_1_38,
	VER_1_381,
	VER_1_39,
	VER_1_391,
	VER_1_392,
	VER_1_4,
	VER_1_41,
	VER_1_411,
	VER_2_1,
	VER_2_12,
	VER_2_13,
	VER_2_14,
	VER_2_15,
	VER_2_151,
	VER_2_16,
	VER_2_17,
	VER_2_18,
	VER_2_19,
	VER_2_2,
	VER_2_21,
	VER_2_22,
	VER_2_3,
	VER_2_31,

	VER_3,
	VER_3_01,
	VER_3_041,

	VER_4_0211,
	VER_4_034,
	VER_4_042,
	VER_4_110,
	VER_4_208,

	VER_5_07,
	VER_5_12,
	VER_5_31x,

	VER_6_015,
	VER_6_034,
	VER_6_037,
	VER_6_037_LINUX,

	VER_IPHONE_1_1,
	VER_IPHONE_1_5,
	VER_IPHONE_1_11
};


std::map<Client, VersionInfo> ClientVersionMap = {
	  { Client::VER_UNKNOWN,     { "",         "(unknown)" } }
	, { Client::VER_NPCSERVER,   { "",         "" } }
	, { Client::VER_1_25,        { "SERV009",  "1.25" } }
	, { Client::VER_1_27,        { "SERV011",  "1.27" } }
	, { Client::VER_1_28,        { "SERV013",  "1.28" } }
	, { Client::VER_1_31,        { "SERV016",  "1.31" } }
	, { Client::VER_1_32,        { "SERV018",  "1.32" } }
	, { Client::VER_1_322,       { "",         "1.32r2" } }
	, { Client::VER_1_323,       { "",         "1.32r3" } }
	, { Client::VER_1_324,       { "",         "1.32r4" } }
	, { Client::VER_1_33,        { "NW20020",  "1.33" } }
	, { Client::VER_1_331,       { "",         "1.33r1" } }
	, { Client::VER_1_34,        { "NW22030",  "1.34" } }
	, { Client::VER_1_341,       { "",         "1.34r1" } }
	, { Client::VER_1_35,        { "NW13040",  "1.35" } }
	, { Client::VER_1_36,        { "NW10050",  "1.36" } }
	, { Client::VER_1_37,        { "NW21050",  "1.37" } }
	, { Client::VER_1_371,       { "",         "1.37r1" } }
	, { Client::VER_1_38,        { "NW22060",  "1.38" } }
	, { Client::VER_1_381,       { "",         "1.38r1" } }
	, { Client::VER_1_39,        { "NW07080",  "1.39" } }
	, { Client::VER_1_391,       { "",         "1.39r1" } }
	, { Client::VER_1_392,       { "",         "1.39r2" } }
	, { Client::VER_1_4,         { "",         "1.4" } }
	, { Client::VER_1_41,        { "",         "1.41" } }
	, { Client::VER_1_411,       { "GNW13110", "1.41r1" } }
	, { Client::VER_2_1,         { "GNW31101", "2.1" } }
	, { Client::VER_2_12,        { "GNW01012", "2.12" } }
	, { Client::VER_2_13,        { "GNW23012", "2.13" } }
	, { Client::VER_2_14,        { "GNW30042", "2.14" } }
	, { Client::VER_2_15,        { "GNW19052", "2.15" } }
	, { Client::VER_2_151,       { "GNW20052", "2.151" } }
	, { Client::VER_2_16,        { "GNW12102", "2.16" } }
	, { Client::VER_2_17,        { "GNW22122", "2.17" } }
	, { Client::VER_2_18,        { "GNW21033", "2.18" } }
	, { Client::VER_2_19,        { "GNW15053", "2.19" } }
	, { Client::VER_2_2,         { "GNW28063", "2.2" } }
	, { Client::VER_2_21,        { "GNW01113", "2.21" } }
	, { Client::VER_2_22,        { "GNW03014", "2.22" } }
	, { Client::VER_2_3,         { "GNW14015", "2.3" } }
	, { Client::VER_2_31,        { "GNW28015", "2.31" } }
	, { Client::VER_3,           { "G3D16053", "3.0" } }
	, { Client::VER_3_01,        { "G3D27063", "3.01" } }
	, { Client::VER_3_041,       { "G3D03014", "3.041" } }
	, { Client::VER_4_0211,      { "G3D28095", "4.0211" } }
	, { Client::VER_4_034,       { "G3D09125", "4.034" } }
	, { Client::VER_4_042,       { "G3D17026", "4.042" } }
	, { Client::VER_4_110,       { "G3D26076", "4.110" } }
	, { Client::VER_4_208,       { "G3D20126", "4.208" } }
	, { Client::VER_5_07,        { "G3D22067", "5.07" } }
	, { Client::VER_5_12,        { "G3D14097", "5.12" } }
	, { Client::VER_5_31x,       { "G3D26090", "5.31x" } }
	, { Client::VER_6_015,       { "G3D3007A", "6.015" } }
	, { Client::VER_6_034,       { "G3D2505C", "6.034/6.035" } }
	, { Client::VER_6_037,       { "G3D0311C", "6.037" } }
	, { Client::VER_6_037_LINUX, { "G3D0511C", "6.037 (Linux)" } }
	, { Client::VER_IPHONE_1_1,  { "G3D04048", "iPhone 1.1" } }
	, { Client::VER_IPHONE_1_5,  { "G3D18010", "iPhone 1.5" } }
	, { Client::VER_IPHONE_1_1,  { "G3D29090", "iPhone 1.11" } }
};


Client getClientVersion(const std::string_view& version)
{
	for (auto i = std::begin(ClientVersionMap); i != std::end(ClientVersionMap); ++i)
	{
		if (i->second.VersionCode == version)
			return i->first;
	}

	return Client::VER_UNKNOWN;
}

VersionInfo getClientVersionInfo(Client version)
{
	auto i = ClientVersionMap.find(version);
	if (i == std::end(ClientVersionMap))
		return {};

	return i->second;
}

} // end namespace graal::versions
