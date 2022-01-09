export module graal.core:random;

import <random>;


export namespace graal
{

class Random
{
public:
	Random() = delete;
	~Random() = delete;

	Random(const Random& other) = delete;
	Random(Random&& other) = delete;
	Random& operator=(const Random& other) = delete;
	Random& operator=(Random&& other) = delete;
	bool operator==(const Random& other) = delete;

public:
	template <std::integral T>
	static T Generate(T max)
	{
		if (!m_seeded) Random::seed();
		std::uniform_int_distribution<T> dist(0, max);
		return dist(Random::m_engine);
	}

	template <std::integral T>
	static T Generate(const std::pair<T, T>& minmax)
	{
		if (!m_seeded) Random::seed();
		std::uniform_int_distribution<T> dist(minmax.first, minmax.second);
		return dist(Random::m_engine);
	}

	template <std::floating_point T>
	static T Generate(T max)
	{
		if (!m_seeded) Random::seed();
		std::uniform_real_distribution<T> dist(0, max);
		return dist(Random::m_engine);
	}

	template <std::floating_point T>
	static T Generate(const std::pair<T, T>& minmax)
	{
		if (!m_seeded) Random::seed();
		std::uniform_real_distribution<T> dist(minmax.first, minmax.second);
		return dist(Random::m_engine);
	}

private:
	static void seed()
	{
		std::random_device device;
		Random::m_engine.seed(device());
		m_seeded = true;
	}

private:
	static std::default_random_engine m_engine;
	static inline bool m_seeded = false;
};

} // end namespace graal

namespace graal
{

std::default_random_engine Random::m_engine;

} // end namespace graal
