// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <type_traits>

#include <spatial/raster/fwd.hpp>

namespace spatial {

template<typename Tp>
struct is_spatial : std::false_type
{};

template<>
struct is_spatial<spatial::raster> : std::true_type
{};

} // namespace spatial
