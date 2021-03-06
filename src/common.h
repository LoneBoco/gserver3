#pragma once

#include <cstdint>
#include <cstddef>
#include <cassert>
#include <array>
#include <memory>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <chrono>
#include <ranges>
#include <concepts>
#include <type_traits>

#include "BabyDI.hpp"

#include <boost/algorithm/string.hpp>

/*
namespace chrono
{
	using clock = std::chrono::steady_clock;
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;
	using file_time = std::chrono::time_point<std::chrono::file_clock>;
}
using namespace std::chrono_literals;
*/

/*
namespace graal
{

class MyClass
{
public:
	MyClass() = default;
	~MyClass() = default;

	MyClass(const MyClass& other) = delete;
	MyClass(MyClass&& other) = delete;
	MyClass& operator=(const MyClass& other) = delete;
	MyClass& operator=(MyClass&& other) = delete;
	bool operator==(const MyClass& other) = delete;
};

} // end namespace graal
*/
