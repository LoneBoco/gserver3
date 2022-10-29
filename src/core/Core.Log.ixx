module;

#include "common.h"

// Don't change this order.  For some reason the compile will fail.
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
//

#include <array>
#include <format>

export module graal.core:log;

//import std.core;
//import std.filesystem;


namespace graal::internal
{
constinit auto spaces = "                                                  ";
}


export namespace graal
{

class Log
{
public:
	Log() = delete;
	~Log() = delete;

	Log(const Log& other) = delete;
	Log(Log&& other) = delete;
	Log& operator=(const Log& other) = delete;
	Log& operator=(Log&& other) = delete;
	bool operator==(const Log& other) = delete;

public:
	template <typename ...Args>
	static void Print(const std::string_view& fmt, const Args&... args)
	{
		std::ostringstream text;

		if (Log::m_wrote_newline)
		{
			auto localtime = std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() }.get_local_time();
			text << std::format("[{:%F %H:%M:%S}] ", std::chrono::floor<std::chrono::seconds>(localtime));
			Log::m_wrote_newline = false;
		}

		text << std::vformat(fmt, std::make_format_args(args...));

		auto s = text.str();

		if (Log::m_file.is_open())
			Log::m_file << s;

		std::cout << s;

		if (s.back() == '\n')
			Log::m_wrote_newline = true;
	}

	template <typename ...Args>
	static void PrintLine(const std::string_view& fmt, const Args&... args)
	{
		Log::Print(fmt, args...);
		Log::Print("\n");
	}

	template <uint32_t N>
	constexpr static std::string_view Indent()
	{
		if constexpr (N == 0)
		{
			return std::string_view{ "" };
		}
		else
		{
			constexpr size_t size = 4 + (N * 2) + 1;
			static_assert(size <= 50, "Indent called with over 50 characters!");

			return std::string_view{ internal::spaces, size};
		}
	}

public:
	static void SetLogFile(const std::filesystem::path& p)
	{
		if (Log::m_file && Log::m_file.is_open())
		{
			Log::m_file.flush();
			Log::m_file.close();
		}
		Log::m_file.open(p, std::ios::binary | std::ios::out | std::ios::app);
	}

private:
	static std::ofstream m_file;
	static bool m_wrote_newline;
};

} // end namespace graal

namespace graal
{

std::ofstream Log::m_file;
bool Log::m_wrote_newline = true;

}
