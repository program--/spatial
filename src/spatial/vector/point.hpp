// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "spatial/detail/types.hpp"

namespace st {

struct point
{
    using value_type      = types::value_type;
    using reference       = value_type&;
    using const_reference = const value_type&;

    struct proxy;

    constexpr point()
      : x_(st::nan)
      , y_(st::nan){};

    constexpr point(value_type x, value_type y)
      : x_(x)
      , y_(y){};

    constexpr reference       x() noexcept { return x_; }
    constexpr const_reference x() const noexcept { return x_; }
    constexpr reference       y() noexcept { return y_; }
    constexpr const_reference y() const noexcept { return y_; }

  private:
    value_type x_;
    value_type y_;
};

struct point::proxy
{
    using value_type      = point::value_type;
    using reference       = point::reference;
    using const_reference = point::const_reference;

    constexpr proxy()     = delete;

    constexpr proxy(reference x, reference y)
      : x_(x)
      , y_(y){};

    constexpr reference       x() noexcept { return x_; }
    constexpr const_reference x() const noexcept { return x_; }
    constexpr reference       y() noexcept { return y_; }
    constexpr const_reference y() const noexcept { return y_; }

  private:
    reference x_;
    reference y_;
};

} // namespace st
