// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <algorithm>

#include <spatial/raster/fwd.hpp>
#include <spatial/detail/types.hpp>
#include <spatial/detail/allocator.hpp>
#include <spatial/raster/axis.hpp>

namespace st {

template<types::size_type ND>
struct mdcell
{};

template<types::size_type ND>
struct mdraster
{
    static_assert(
      ND > 2,
      "mdraster must have ND greater than 2. "
      "Use st::raster for ND == 2."
    );

    using size_type       = types::size_type;
    using value_type      = types::value_type;
    using reference       = mdcell<ND>;
    using const_reference = const mdcell<ND>;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = reference;
    using const_iterator  = const_reference;
    using allocator_type =
      std::unique_ptr<detail::virtual_allocator<value_type>>;

    mdraster(
      std::array<size_type, ND> dimensions,
      types::extent             ext,
      allocator_type            allocator = nullptr
    );

    ~mdraster();

    template<typename... Indices>
    reference at(Indices... indices);
    reference at(std::array<size_type, ND>);
    template<typename... Indices>
    const_reference at(Indices... indices) const;
    const_reference at(std::array<size_type, ND>) const;
    reference operator[](std::array<size_type, ND>) noexcept;
    const_reference operator[](std::array<size_type, ND>) const noexcept;
    const axis&    axis(size_type n) const noexcept;
    size_type      size(size_type n) const noexcept;
    size_type      size() const noexcept;
    iterator       begin() noexcept;
    const_iterator begin() const noexcept;
    iterator       end() noexcept;
    const_iterator end() const noexcept;

    template<typename Functor, typename... Args>
    auto apply(Functor&& f, Args&&... args)
    {
        return f(*this, std::forward<Args>(args)...);
    }

    template<typename Functor>
    void apply(Functor&& f)
    {
        std::for_each(begin(), end(), f);
    }
};

} // namespace st
