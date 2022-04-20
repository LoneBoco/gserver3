#pragma once

namespace chrono
{
	using clock = std::chrono::steady_clock;
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;
	using file_time = std::chrono::time_point<std::chrono::file_clock>;
}
using namespace std::chrono_literals;
