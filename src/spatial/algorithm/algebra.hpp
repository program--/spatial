// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <spatial/algorithm/scope.hpp>
#include "spatial/detail/types.hpp"
#include <spatial/raster/fwd.hpp>

namespace st {

template<typename Model, typename Scope = void>
struct add;

template<>
struct add<raster, scope::local>;

template<>
struct add<raster, scope::focal>;

template<>
struct add<raster, scope::zonal>;

template<>
struct add<raster, scope::global>;

} // namespace st
