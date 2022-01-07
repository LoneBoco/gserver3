export module graal.packet:utilities;

import "common.h";
import <array>;
import <ranges>;


export namespace graal::packet
{

template <std::size_t N>
constexpr std::array<uint8_t, N> WRITEGRAAL(uint64_t data)
{
	if constexpr (N == 1) data = std::min(data, 223ull);
	if constexpr (N == 2) data = std::min(data, 28767ull);
	if constexpr (N == 3) data = std::min(data, 3682399ull);
	if constexpr (N == 4) data = std::min(data, 471347295ull);
	if constexpr (N == 5) data = std::min(data, 0xFFFFFFFFull);
	static_assert(N > 0 && N <= 5, "WRITEGRAAL only supports 1-5 bytes of data.");

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
constexpr std::array<uint8_t, N> WRITE(uint64_t data)
{
	static_assert(N > 0 && N <= 5, "WRITE only supports 1-5 bytes of data.");

	std::array<uint8_t, N> result;
	for (int i = 0; i < N; ++i)
	{
		int shift = (N - 1 - i) * 8;
		result[i] = static_cast<uint8_t>(data >> shift);
	}

	return result;
}


template <const std::size_t N, std::integral T>
struct READGRAAL_t
{
private:
	T& output;

public:
	READGRAAL_t() = delete;
	constexpr READGRAAL_t(T& out) : output(out)
	{
		static_assert(sizeof(out) >= N, "READGRAAL output is not large enough.");
	}

	template <std::size_t N>
	constexpr std::ranges::view auto operator()(std::ranges::view auto&& r) const
	{
		//static_assert(std::ranges::size(r) >= N, "READGRAAL input not big enough.");

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


template <const std::size_t N, std::integral T>
struct READ_t
{
private:
	T& output;

public:
	READ_t() = delete;
	constexpr READ_t(T& out) : output(out)
	{
		static_assert(sizeof(out) >= N, "READ output is not large enough.");
	}

	template <std::size_t N>
	constexpr std::ranges::view auto operator()(std::ranges::view auto&& r) const
	{
		//static_assert(std::ranges::size(r) >= N, "READ input not big enough.");

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
constexpr auto READGRAAL(auto& out)
{
	return READGRAAL_t<N, std::remove_reference<decltype(out)>::type>(out);
}


template <std::size_t N>
constexpr auto READ(auto& out)
{
	return READ_t<N, std::remove_reference<decltype(out)>::type>(out);
}

} // end namespace graal::packet



export template <std::size_t N, std::integral T>
constexpr auto operator >> (std::ranges::range auto&& r, const graal::packet::READGRAAL_t<N, T>& out)
{
	return out.operator()<N>(std::views::all(r));
}

export template <std::size_t N, std::integral T>
constexpr auto operator >> (std::ranges::view auto&& r, const graal::packet::READGRAAL_t<N, T>& out)
{
	return out.operator()<N>(std::forward<decltype(r)>(r));
}


export template <std::size_t N, std::integral T>
constexpr auto operator >> (std::ranges::range auto&& r, const graal::packet::READ_t<N, T>& out)
{
	return out.operator()<N>(std::views::all(r));
}

export template <std::size_t N, std::integral T>
constexpr auto operator >> (std::ranges::view auto&& r, const graal::packet::READ_t<N, T>& out)
{
	return out.operator()<N>(std::forward<decltype(r)>(r));
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
	requires std::forward_iterator<typename T::const_iterator>
		//&& has_empty_function<T>
PacketData& operator<<(PacketData& lhs, const T& rhs)
{
	if (rhs.empty()) return lhs;
	lhs.insert(std::end(lhs), std::begin(rhs), std::end(rhs));
	return lhs;
}

//}
