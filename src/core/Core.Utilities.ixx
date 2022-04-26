module;

#include "common.h"

export module graal.core:utilities;


export namespace graal
{

std::string removeComments(const std::string& code, const std::string_view& newLine)
{
	std::string result{ code };

	size_t marker = 0;

	// Remove // comments.
	size_t comment = 0;
	while ((comment = result.find("//", marker)) != std::string::npos)
	{
		marker = comment + 1;

		// Check for URLs (http://)
		if (comment > 0 && result[comment - 1] == ':')
			continue;

		// Check for //#CLIENTSIDE
		if (result.substr(comment, 13) == "//#CLIENTSIDE")
			continue;

		// Find the end of the line.
		auto eol = result.find(newLine, comment);
		if (eol != std::string::npos)
		{
			auto length = (eol + 1) - comment;
			result.erase(comment, length);
		}
	}

	// Remove /* ... */ comments.
	marker = 0;
	while ((comment = result.find("/*", marker)) != std::string::npos)
	{
		marker = comment + 1;

		auto eol = result.find("*/", marker);
		if (eol != std::string::npos)
		{
			auto length = (eol + 1) - comment;
			result.erase(comment, length);
		}
	}

	return result;
}

} // end namespace graal
