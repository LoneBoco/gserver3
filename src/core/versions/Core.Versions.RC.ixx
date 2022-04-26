module;

#include "common.h"

export module graal.core.versions:rc;
import :base;


export namespace graal::versions
{

enum class RC
{
	VER_UNKNOWN,
	VER_1_010,
	VER_1_1,
	VER_2
};

std::map<RC, VersionInfo> RCVersionMap = {
	  { RC::VER_UNKNOWN, { "",         "(unknown)" } }
	, { RC::VER_1_010,   { "GSERV023", "1.01" } }
	, { RC::VER_1_1,     { "GSERV024", "1.1" } }
	, { RC::VER_2,       { "GSERV025", "2" } }
};


RC getRCVersion(const std::string_view& version)
{
	for (auto i = std::begin(RCVersionMap); i != std::end(RCVersionMap); ++i)
	{
		if (i->second.VersionCode == version)
			return i->first;
	}

	return RC::VER_UNKNOWN;
}

VersionInfo getRCVersionInfo(RC version)
{
	auto i = RCVersionMap.find(version);
	if (i == std::end(RCVersionMap))
		return {};

	return i->second;
}

} // end namespace graal::versions
