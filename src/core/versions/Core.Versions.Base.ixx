module;

#include "common.h"

export module graal.core.versions:base;


export namespace graal::versions
{

struct VersionInfo
{
	std::string_view VersionCode;
	std::string_view VersionFormatted;
};

} // end namespace graal::versions
