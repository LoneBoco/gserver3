module;

#include "common.h"

export module graal.core:ranges;

//import std.core;


namespace rng = std::ranges;

// This was taken from Stack Overflow.
// https://stackoverflow.com/questions/58808030/range-view-to-stdvector


export
namespace graal
{

namespace detail
{
    // Type acts as a tag to find the correct operator| overload
    template <typename C>
    struct to_helper {};

    template <typename C, typename P>
    struct split_helper
    {
        split_helper(P&& p) : pattern(std::forward<P>(p)) {}
        P pattern;
    };

    // This actually does the work
    template <typename Container, rng::range R>
        requires std::convertible_to<rng::range_value_t<R>, typename Container::value_type> && !std::same_as<R, rng::split_view>
    Container operator|(R&& r, to_helper<Container>)
    {
        return Container{ r.begin(), r.end() };
    }

    template <typename Container, rng::forward_range V, rng::forward_range Pattern>
    Container operator|(rng::split_view<V, Pattern>&& r, to_helper<Container>)
    {
        using ct = typename Container::value_type;

        Container result;
        for (const auto x : r)
            result.emplace(std::end(result), rng::begin(x), rng::end(x));

        return result;
    }

    template <typename Container, typename Pattern>
    Container operator|(rng::range auto&& r, split_helper<Container, Pattern> h)
    {
        return rng::views::all(r) | rng::views::split(std::move(h.pattern)) | to<Container>();
    }

    template <typename Container, typename Pattern>
    Container operator|(rng::view auto&& r, split_helper<Container, Pattern> h)
    {
        return r | rng::views::split(std::move(h.pattern)) | to<Container>();
    }
}

// Couldn't find an concept for container, however a
// container is a range, but not a view.
template <rng::range Container> requires (!rng::view<Container>)
auto to()
{
    return detail::to_helper<Container>{};
}

template <typename Container, typename Pattern>
auto split(Pattern pattern)
{
    return detail::split_helper<Container, Pattern>{ std::move(pattern) };
}

} // end namespace graal
