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

struct cell;
struct axis;
struct raster;

template<types::size_type ND>
struct mdraster;

template<>
struct mdraster<dynamic>;

template<types::size_type ND>
struct mdcell;

template<>
struct mdcell<dynamic>;

} // namespace st
