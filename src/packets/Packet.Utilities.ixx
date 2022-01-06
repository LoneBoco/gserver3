export module graal.packet:utilities;

import "common.h";
import <array>;


export namespace graal::packet
{

template <std::size_t N>
constexpr
	std::array<uint8_t, N> GRAALBYTE(uint64_t data)
{
	if constexpr (N == 1) data = std::min(data, 223ull);
	if constexpr (N == 2) data = std::min(data, 28767ull);
	if constexpr (N == 3) data = std::min(data, 3682399ull);
	if constexpr (N == 4) data = std::min(data, 471347295ull);
	if constexpr (N == 5) data = std::min(data, 0xFFFFFFFFull);
	static_assert(N > 0 && N <= 5, "GRAALBYTE only supports 1-5 bytes of data.");

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

} // end namespace graal::packet


// This is so stupid and should not be required.  Why?  This should already exist in Packet.ixx.
namespace graal::packet
{
	using PacketData = std::vector<uint8_t>;
}
using graal::packet::PacketData;


namespace graal
{

export template <typename T>// requires std::is_same<T, decltype(uint8_t)>
PacketData& operator<<(PacketData& lhs, const uint8_t& rhs)
{
	lhs.insert(std::end(lhs), rhs);
	return lhs;
}

export template <typename T>
	requires std::forward_iterator<typename T::const_iterator> //&& has_empty_function<T>
PacketData& operator<<(PacketData& lhs, const T& rhs)
{
	if (rhs.empty()) return lhs;
	lhs.insert(std::end(lhs), std::begin(rhs), std::end(rhs));
	return lhs;
}

}
