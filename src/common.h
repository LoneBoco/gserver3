#pragma once

import <cstdint>;
import <cstddef>;
import <memory>;
import <string>;
import <vector>;
import <map>;
import <functional>;
import <algorithm>;
import <chrono>;
import <ranges>;
import <concepts>;

//import <numeric>;
//import <locale>;
//import <atomic>;

//import "BabyDI.hpp";

import <boost/algorithm/string.hpp>;


namespace chrono
{
	using clock = std::chrono::steady_clock;
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;
	using file_time = std::chrono::time_point<std::chrono::file_clock>;
}
using namespace std::chrono_literals;

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
