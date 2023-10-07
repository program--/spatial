// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <spatial/io/driver.hpp>

namespace st {
namespace io {

template<typename Format, typename Model, typename... Args>
Model deserialize(
  driver<Format>                    fmt,
  typename driver<Format>::buffer&& buf,
  Args&&... args
)
{
    return fmt.deserialize(
      std::forward<typename driver<Format>::buffer>(buf),
      std::forward<Args>(args)...
    );
}

template<typename Format, typename Model, typename... Args>
Model deserialize(typename driver<Format>::buffer&& buf, Args&&... args)
{
    return deserialize(
      driver<Format>{},
      std::forward<typename driver<Format>::buffer>(buf),
      std::forward<Args>(args)...
    );
}

} // namespace io
} // namespace st
