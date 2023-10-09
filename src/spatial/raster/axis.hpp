// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cmath>

#include <spatial/raster/fwd.hpp>
#include <spatial/detail/types.hpp>

namespace st {

struct axis
{
    using size_type  = st::types::size_type;
    using value_type = st::types::value_type;

    constexpr axis(value_type from, value_type to, size_type length)
      : len_(length)
      , from_(from)
      , to_(to){};

    constexpr size_type size() const noexcept { return len_; }

    constexpr size_type along(value_type value)
    {
        const auto diff = (to_ - from_) / static_cast<double>(len_ - 1);
        const auto compute_bound = [&](auto x) { return from_ + (diff * x); };
        size_type  l             = 0U;
        size_type  r             = len_;

        while (l < r) {
            const auto m = std::floor((l + r) / 2.0);
            if (compute_bound(m) > value) {
                r = m;
            } else {
                l = m + 1;
            }
        }

        const size_type right         = r - 1;
        const size_type left          = right - 1;
        const bool      out_of_bounds = right >= len_;
        const bool      is_left       = compute_bound(right) - value > 0.5;

        if (out_of_bounds) {
            return static_cast<size_type>(-1);
        } else if (is_left) {
            return left;
        } else {
            return right;
        }
    }

  private:
    size_type  len_;
    value_type from_;
    value_type to_;
};

} // namespace st
