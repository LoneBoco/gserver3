module;

#include "common.h"

export module graal.core:position;

//import std.core;


export namespace graal
{

template <typename T>
	requires std::integral<T> || std::floating_point<T>
struct Position2D
{
public:
	Position2D() = default;
	~Position2D() = default;

	Position2D(const Position2D<T>& other) = default;
	Position2D(Position2D<T>&& other) = default;
	Position2D& operator=(const Position2D<T>& other) = default;
	Position2D& operator=(Position2D<T>&& other) = default;

	bool operator==(const Position2D<T>& other)
	{
		return X == other.X && Y == other.Y;
	}

public:
	Position2D(const T& x, const T& y) : X(x), Y(y) {}

public:
	T X;
	T Y;
};

template <typename T>
	requires std::integral<T> || std::floating_point<T>
struct Size2D
{
public:
	Size2D() = default;
	~Size2D() = default;

	Size2D(const Size2D<T>& other) = default;
	Size2D(Size2D<T>&& other) = default;
	Size2D& operator=(const Size2D<T>& other) = default;
	Size2D& operator=(Size2D<T>&& other) = default;

	bool operator==(const Size2D<T>& other)
	{
		return Width == other.Width && Height == other.Height;
	}

public:
	Size2D(const T& width, const T& height) : Width(width), Height(height) {}

public:
	T Width;
	T Height;
};

// Capital 2D
using Position2Di = Position2D<int>;
using Position2Df = Position2D<float>;
using Size2Di = Size2D<int>;
using Size2Df = Size2D<float>;

// Lowercase 2d
using Position2di = Position2D<int>;
using Position2df = Position2D<float>;
using Size2di = Size2D<int>;
using Size2df = Size2D<float>;

} // end namespace graal
