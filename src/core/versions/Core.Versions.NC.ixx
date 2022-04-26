module;

#include "common.h"

export module graal.core.versions:nc;
import :base;


export namespace graal::versions
{

enum class NC
{
	VER_UNKNOWN,
	VER_1_1,
	VER_2_1
};

std::map<NC, VersionInfo> NCVersionMap = {
	  { NC::VER_UNKNOWN, { "",         "(unknown)" } }
	, { NC::VER_1_1,     { "NCL11012", "1.1" } }
	, { NC::VER_2_1,     { "NCL21075", "2.1" } }
};


NC getNCVersion(const std::string_view& version)
{
	for (auto i = std::begin(NCVersionMap); i != std::end(NCVersionMap); ++i)
	{
		if (i->second.VersionCode == version)
			return i->first;
	}

	return NC::VER_UNKNOWN;
}

VersionInfo getNCVersionInfo(NC version)
{
	auto i = NCVersionMap.find(version);
	if (i == std::end(NCVersionMap))
		return {};

	return i->second;
}

} // end namespace graal::versions
