// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <spatial/io/driver.hpp>

namespace spatial {
namespace io {
namespace format {

struct wkb : driver<wkb>
{};

} // namespace format
} // namespace io
} // namespace spatial
