// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <spatial/detail/traits.hpp>

namespace st {

template<>
struct is_spatial<st::raster> : std::true_type
{};

template<types::size_type ND>
struct is_spatial<st::mdraster<ND>> : std::true_type
{};

} // namespace st
