module;

#include "common.h"

export module graal.packet:utilities;

/*
import <cassert>;

import std.core;
import std.memory;
*/


export namespace graal::packet
{

template <std::size_t N>
constexpr std::array<uint8_t, N> WriteGraalByte(uint64_t data)
{
	if constexpr (N == 1) data = std::min(data, 223ull);
	if constexpr (N == 2) data = std::min(data, 28767ull);
	if constexpr (N == 3) data = std::min(data, 3682399ull);
	if constexpr (N == 4) data = std::min(data, 471347295ull);
	if constexpr (N == 5) data = std::min(data, 0xFFFFFFFFull);
	static_assert(N > 0 && N <= 5, "WriteGraalByte only supports 1-5 bytes of data.");

	std::array<uint8_t, N> result;
	for (int i = 0; i < N - 1; ++i)
	{
		int shift = (N - 1 - i) * 7;
		result[i] = static_cast<uint8_t>(data >> shift);
		if (result[i] > 223)
			result[i] = 223;

		data -= result[i] << shift;
		result[i] += 32;
	}

	result[N - 1] = static_cast<uint8_t>(data);
	result[N - 1] += 32;

	return result;
}

template <std::size_t N>
constexpr std::array<uint8_t, N> WriteByte(uint64_t data)
{
	static_assert(N > 0 && N <= 5, "WriteByte only supports 1-5 bytes of data.");

	std::array<uint8_t, N> result;
	for (int i = 0; i < N; ++i)
	{
		int shift = (N - 1 - i) * 8;
		result[i] = static_cast<uint8_t>(data >> shift);
	}

	return result;
}

template <std::size_t N>
constexpr std::vector<uint8_t> WriteClassicString(const std::string& data)
{
	auto len = WriteGraalByte<N>(std::ranges::size(data));
	
	std::vector<uint8_t> result{ std::begin(len), std::end(len) };
	result.insert(std::end(result), std::begin(data), std::end(data));
	return result;
}

template <std::size_t N>
constexpr std::vector<uint8_t> WriteString(const std::string& data)
{
	auto len = WriteByte<N>(std::ranges::size(data));

	std::vector<uint8_t> result{ std::begin(len), std::end(len) };
	result.insert(std::end(result), std::begin(data), std::end(data));
	return result;
}


template <const std::size_t N, std::integral T>
struct ReadGraalByte_t
{
private:
	T& output;

public:
	ReadGraalByte_t() = delete;
	constexpr ReadGraalByte_t(T& out) : output(out)
	{
		static_assert(sizeof(out) >= N, "ReadGraalByte output is not large enough.");
	}

	template <std::size_t N>
	constexpr std::ranges::view auto operator()(std::ranges::view auto&& r) const
	{
		//static_assert(std::ranges::size(r) >= N, "ReadGraalByte input not big enough.");

		output = 0;
		auto b = std::begin(r);
		auto e = std::end(r);

		for (auto i = 0; i < N - 1 && b != e; ++i)
		{
			auto val = *b;
			output += val;
			output <<= 7;
			b = std::next(b);
		}

		assert(b != e);
		output += *b;

		if constexpr (N == 1) output -= 32;
		if constexpr (N == 2) output -= 0x1020;
		if constexpr (N == 3) output -= 0x81020;
		if constexpr (N == 4) output -= 0x4081020;
		if constexpr (N == 5) output -= 0x4081020;

		return r | std::views::drop(N);
	}
};

template <std::size_t N>
constexpr auto ReadGraalByte(auto& out)
{
	return ReadGraalByte_t<N, std::remove_reference<decltype(out)>::type>(out);
}


template <const std::size_t N, std::integral T>
struct ReadByte_t
{
private:
	T& output;

public:
	ReadByte_t() = delete;
	constexpr ReadByte_t(T& out) : output(out)
	{
		static_assert(sizeof(out) >= N, "ReadByte output is not large enough.");
	}

	template <std::size_t N>
	constexpr std::ranges::view auto operator()(std::ranges::view auto&& r) const
	{
		//static_assert(std::ranges::size(r) >= N, "ReadByte input not big enough.");

		output = 0;
		auto b = std::begin(r);
		auto e = std::end(r);

		for (auto i = 0; i < N - 1 && b != e; ++i)
		{
			auto val = *b;
			output += val;
			output <<= 8;
			b = std::next(b);
		}

		assert(b != e);
		output += *b;

		return r | std::views::drop(N);
	}
};

template <std::size_t N>
constexpr auto ReadByte(auto& out)
{
	return ReadByte_t<N, std::remove_reference<decltype(out)>::type>(out);
}


template <const std::size_t N>
struct ReadClassicString_t
{
private:
	std::string& output;

public:
	ReadClassicString_t() = delete;
	constexpr ReadClassicString_t(std::string& out) : output(out)
	{}

	template <std::size_t N>
	constexpr std::ranges::view auto operator()(std::ranges::view auto&& r) const
	{
		//static_assert(std::ranges::size(r) >= N, "READ input not big enough.");

		if constexpr (N == 0)
		{
			auto b = std::begin(r);
			auto e = std::end(r);

			output.clear();
			output.insert(std::begin(output), b, e);
			return e;
		}
		else
		{
			uint64_t string_length;

			auto reader = ReadGraalByte<N>(string_length);
			auto new_range = reader.operator()<N>(std::forward<decltype(r)>(r));

			auto b = std::begin(new_range);
			auto e = std::next(b, string_length);

			output.clear();
			output.insert(std::begin(output), b, e);

			return new_range | std::views::drop(string_length);
		}
	}
};

template <std::size_t N>
constexpr auto ReadClassicString(std::string& out)
{
	return ReadClassicString_t<N>(out);
}


template <const std::size_t N>
struct ReadString_t
{
private:
	std::string& output;

public:
	ReadString_t() = delete;
	constexpr ReadString_t(std::string& out) : output(out)
	{}

	template <std::size_t N>
	constexpr std::ranges::view auto operator()(std::ranges::view auto&& r) const
	{
		//static_assert(std::ranges::size(r) >= N, "READ input not big enough.");

		if constexpr (N == 0)
		{
			auto b = std::begin(r);
			auto e = std::end(r);

			output.clear();
			output.insert(std::begin(output), b, e);
			return e;
		}
		else
		{
			uint64_t string_length;

			auto reader = ReadByte<N>(string_length);
			auto new_range = reader.operator() < N > (std::forward<decltype(r)>(r));

			auto b = std::begin(new_range);
			auto e = std::next(b, string_length);

			output.clear();
			output.insert(std::begin(output), b, e);

			return new_range | std::views::drop(string_length);
		}
	}
};

template <std::size_t N>
constexpr auto ReadString(std::string& out)
{
	return ReadString_t<N>(out);
}


constexpr auto ReadRawString(std::string& out)
{
	return ReadString_t<0>(out);
}


} // end namespace graal::packet



export template <std::size_t N, std::integral T>
constexpr auto operator>> (std::ranges::range auto&& r, const graal::packet::ReadGraalByte_t<N, T>& out)
{
	return out.operator()<N>(std::views::all(r));
}

export template <std::size_t N, std::integral T>
constexpr auto operator>> (std::ranges::view auto&& r, const graal::packet::ReadGraalByte_t<N, T>& out)
{
	return out.operator()<N>(std::forward<decltype(r)>(r));
}



export template <std::size_t N, std::integral T>
constexpr auto operator>> (std::ranges::range auto&& r, const graal::packet::ReadByte_t<N, T>& out)
{
	return out.operator()<N>(std::views::all(r));
}

export template <std::size_t N, std::integral T>
constexpr auto operator>> (std::ranges::view auto&& r, const graal::packet::ReadByte_t<N, T>& out)
{
	return out.operator()<N>(std::forward<decltype(r)>(r));
}


export template <std::size_t N>
constexpr auto operator>> (std::ranges::range auto&& r, const graal::packet::ReadClassicString_t<N>& out)
{
	return out.operator()<N>(std::views::all(r));
}

export template <std::size_t N>
constexpr auto operator>> (std::ranges::view auto&& r, const graal::packet::ReadClassicString_t<N>& out)
{
	return out.operator()<N>(std::forward<decltype(r)>(r));
}


export template <std::size_t N>
constexpr auto operator>> (std::ranges::range auto&& r, const graal::packet::ReadString_t<N>& out)
{
	return out.operator()<N>(std::views::all(r));
}

export template <std::size_t N>
constexpr auto operator>> (std::ranges::view auto&& r, const graal::packet::ReadString_t<N>& out)
{
	return out.operator()<N>(std::forward<decltype(r)>(r));
}



export
constexpr auto operator>> (std::ranges::view auto&& r, std::string& out)
{
	out.clear();
	out.insert(std::begin(out), std::begin(r), std::end(r));
	return std::end(r);
}


// This is so stupid and should not be required.  Why?  This should already exist in Packet.ixx.
namespace graal::packet
{
	using PacketData = std::vector<uint8_t>;
}
using graal::packet::PacketData;


//namespace graal
//{

export template <typename T>// requires std::is_same<T, decltype(uint8_t)>
PacketData& operator<<(PacketData& lhs, const uint8_t& rhs)
{
	lhs.insert(std::end(lhs), rhs);
	return lhs;
}

export template <typename T>
	//requires std::forward_iterator<typename T::const_iterator>
		//&& has_empty_function<T>
PacketData& operator<<(PacketData& lhs, const T& rhs)
{
	if (rhs.empty()) return lhs;
	lhs.insert(std::end(lhs), std::begin(rhs), std::end(rhs));
	return lhs;
}

//}
