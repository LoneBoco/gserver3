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

import <boost/algorithm/string.hpp>;

import "BabyDI.hpp";

namespace chrono
{
	using clock = std::chrono::steady_clock;
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;
}
using namespace std::chrono_literals;
