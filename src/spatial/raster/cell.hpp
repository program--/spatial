// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <iterator>

#include <spatial/raster/fwd.hpp>
#include <spatial/detail/types.hpp>

namespace st {

struct cell
{
    using size_type       = st::types::size_type;
    using difference_type = st::types::difference_type;
    using value_type      = st::types::value_type;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator_tag    = std::bidirectional_iterator_tag;

    static cell invalid;

    cell();
    cell(
      pointer   ptr,
      size_type row,
      size_type col,
      size_type nrows,
      size_type ncols
    );

    cell& operator=(value_type) noexcept;

    reference                       operator*() noexcept;
    const_reference                 operator*() const noexcept;
    pointer                         operator->() noexcept;
    const_pointer                   operator->() const noexcept;
    cell                            left() const noexcept;
    cell                            right() const noexcept;
    cell                            top() const noexcept;
    cell                            bottom() const noexcept;
    cell                            top_left() const noexcept;
    cell                            top_right() const noexcept;
    cell                            bottom_left() const noexcept;
    cell                            bottom_right() const noexcept;
    std::pair<size_type, size_type> index() const noexcept;

    cell&                           operator++() noexcept;
    cell                            operator++(int) noexcept;
    cell&                           operator--() noexcept;
    cell                            operator--(int) noexcept;
    bool                            operator==(const cell&) const noexcept;
    bool                            operator!=(const cell&) const noexcept;
    bool operator==(value_type) const noexcept;
    bool operator!=(value_type) const noexcept;

    operator pointer() noexcept;
    operator const_pointer() const noexcept;

  private:
    difference_type lshift() const noexcept;
    difference_type rshift() const noexcept;
    difference_type ushift() const noexcept;
    difference_type dshift() const noexcept;

    size_type       row_;
    size_type       col_;
    size_type       nrows_;
    size_type       ncols_;
    pointer         cell_;
};

} // namespace st
