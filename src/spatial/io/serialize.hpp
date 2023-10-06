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

template<typename Format, typename Model, typename... Args>
auto serialize(driver<Format> fmt, Model&& model, Args&&... args) ->
  typename driver<Format>::buffer
{
    return fmt.serialize(
      std::forward<Model>(model), std::forward<Args>(args)...
    );
}

template<typename Format, typename Model, typename... Args>
auto serialize(Model&& model, Args&&... args)
{
    return serialize(
      driver<Format>{}, std::forward<Model>(model), std::forward<Args>(args)...
    );
}

} // namespace io
} // namespace spatial
