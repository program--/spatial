// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <vector>
#include <cstdint>

namespace spatial {
namespace io {

template<typename Derived>
struct driver
{
    using byte_type   = uint8_t;
    using buffer      = std::vector<byte_type>;

    virtual ~driver() = default;

    template<typename Model, typename... Args>
    buffer serialize(Model&& model, Args&&... args)
    {
        return interface()->serialize_impl(
          std::forward<Model>(model), std::forward<Args>(args)...
        );
    }

    template<typename Model, typename... Args>
    Model deserialize(buffer&& buf, Args&&... args)
    {
        return interface()->deserialize_impl(
          std::forward<buffer>(buf), std::forward<Args>(args)...
        );
    }

  private:
    using derived_type = Derived;
    driver()           = default;

    friend derived_type;

    constexpr derived_type* interface() const noexcept
    {
        return static_cast<derived_type*>(this);
    }
};

} // namespace io
} // namespace spatial
