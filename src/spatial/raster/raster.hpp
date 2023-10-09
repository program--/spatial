// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <algorithm>
#include <utility>

#include <spatial/raster/fwd.hpp>
#include <spatial/detail/types.hpp>
#include <spatial/detail/functor.hpp>
#include <spatial/detail/virtual_allocator.hpp>
#include <spatial/raster/axis.hpp>
#include <spatial/raster/cell.hpp>

namespace st {

struct raster
{
    using size_type       = types::size_type;
    using value_type      = types::value_type;
    using reference       = cell;
    using const_reference = const cell;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = reference;
    using const_iterator  = const_reference;
    using allocator_type =
      std::unique_ptr<detail::virtual_allocator<value_type>>;

    raster(
      const size_type     nrows,
      const size_type     ncols,
      const types::extent ext,
      allocator_type      allocator = nullptr
    );

    ~raster();

    const axis&    xaxis() const noexcept;
    const axis&    yaxis() const noexcept;
    reference      at(size_type col, size_type row);
    reference      operator[](std::pair<size_type, size_type> xy) noexcept;
    size_type      nrows() const noexcept;
    size_type      ncols() const noexcept;
    size_type      ncells() const noexcept;
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

  private:
    axis           xaxis_;
    axis           yaxis_;
    allocator_type alloc_;
    pointer        data_;
};

} // namespace st
