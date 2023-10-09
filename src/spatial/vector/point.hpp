// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <type_traits>
#include <utility>

#include <spatial/detail/types.hpp>
#include <spatial/detail/traits.hpp>
#include <spatial/detail/proxy.hpp>

namespace st {

namespace detail {

template<typename Tp, bool = std::is_reference<Tp>::value>
struct point_base;

template<typename Tp>
struct point_base<Tp, false>
{
    static_assert(
      !std::is_pointer<Tp>::value,
      "point value type cannot be a pointer"
    );

    using value_type      = detail::remove_cvref_t<Tp>;
    using reference       = value_type&;
    using const_reference = const value_type&;

    constexpr point_base()
      : xy_(st::nan, st::nan){};

    constexpr point_base(Tp x, Tp y)
      : xy_(x, y){};

    constexpr reference       x() noexcept { return xy_.first; }
    constexpr const_reference x() const noexcept { return xy_.first; }
    constexpr reference       y() noexcept { return xy_.second; }
    constexpr const_reference y() const noexcept { return xy_.second; }

  private:
    std::pair<Tp, Tp> xy_;
};

template<typename Tp>
struct point_base<Tp, true>
{
    static_assert(
      !std::is_pointer<Tp>::value,
      "point value type cannot be a pointer"
    );

    using value_type       = detail::remove_cvref_t<Tp>;
    using reference        = value_type&;
    using const_reference  = const value_type&;

    constexpr point_base() = delete;

    template<typename Up>
    constexpr point_base(point_base<Up>& p)
      : xy_(p.x(), p.y()){};

    template<typename Up>
    constexpr point_base& operator=(point_base<Up>& p)
    {
        this->xy_ = { p.x(), p.y() };
        return *this;
    }

    constexpr reference       x() noexcept { return xy_.first; }
    constexpr const_reference x() const noexcept { return xy_.first; }
    constexpr reference       y() noexcept { return xy_.second; }
    constexpr const_reference y() const noexcept { return xy_.second; }

  private:
    std::pair<Tp, Tp> xy_;
};

} // namespace detail

using point           = detail::point_base<double>;
using point_ref       = detail::point_base<double&>;
using const_point_ref = const detail::point_base<const double&>;

} // namespace st
