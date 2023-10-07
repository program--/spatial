// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "spatial/detail/types.hpp"
#include <spatial/vector/point.hpp>
#include <spatial/detail/allocator.hpp>

namespace st {

struct linestring
{
    using element_type    = st::point;
    using size_type       = types::size_type;
    using value_type      = element_type::value_type;
    using reference       = element_type::proxy;
    using const_reference = const element_type::proxy;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using allocator_type =
      std::unique_ptr<detail::virtual_allocator<value_type>>;

    struct iterator;
    using const_iterator = const iterator;

    reference       front() noexcept;
    const_reference front() const noexcept;
    reference       back() noexcept;
    const_reference back() const noexcept;
    reference       at(size_type n);
    const_reference at(size_type n) const;
    reference       operator[](size_type n) noexcept;
    const_reference operator[](size_type n) const noexcept;
    size_type       size() const noexcept;
    void            push_back(point);
    void            push_back(value_type x, value_type y);
    iterator        begin() noexcept;
    const_iterator  begin() const noexcept;
    iterator        end() noexcept;
    const_iterator  end() const noexcept;

  private:
    allocator_type alloc_;
    pointer        data_;
};

} // namespace st
