// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "spatial/vector/detail/fwd.hpp"
#include <spatial/detail/traits.hpp>

namespace st {

template<>
struct is_spatial<point> : std::true_type
{};

template<>
struct is_spatial<linestring> : std::true_type
{};

template<>
struct is_spatial<polygon> : std::true_type
{};

template<>
struct is_spatial<multi<point>> : std::true_type
{};

template<>
struct is_spatial<multi<linestring>> : std::true_type
{};

template<>
struct is_spatial<multi<polygon>> : std::true_type
{};

} // namespace st
