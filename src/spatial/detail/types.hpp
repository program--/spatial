// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cmath>
#include <cstddef>

namespace st {
namespace types {

using size_type       = std::size_t;
using difference_type = std::ptrdiff_t;
using value_type      = double;

struct extent
{
    double xmax;
    double xmin;
    double ymax;
    double ymin;
};

} // namespace types

constexpr auto dynamic = static_cast<types::size_type>(-1);
constexpr auto nan     = NAN;

} // namespace st
