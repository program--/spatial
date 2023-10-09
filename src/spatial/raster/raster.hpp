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

//! Conventional Single-band 2D Raster
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

    //! Construct a new single-band raster.
    //!
    //! @param nrows Number of rows.
    //! @param ncols Number of columns.
    //! @param ext   Geographical extent of this raster.
    //! @param allocator Virtual allocator to use for allocating cells.
    raster(
      const size_type     nrows,
      const size_type     ncols,
      const types::extent ext,
      allocator_type      allocator = nullptr
    );

    //! Raster destructor
    ~raster();

    //! Get the x-axis of this raster.
    //! @returns (const) reference to a st::axis.
    const axis& xaxis() const noexcept;

    //! Get the y-axis of this raster.
    //! @returns (const) reference to a st::axis.
    const axis& yaxis() const noexcept;

    //! Reference a cell within this raster.
    //! @param col Column index.
    //! @param row Row index.
    //! @throws std::out_of_range if `(col, row)` is not a valid cell index.
    //! @returns st::cell
    reference at(size_type col, size_type row);

    //! Reference a cell within this raster (without bounds checks)
    //! @param xy a `(col, row)` pair
    //! @returns st::cell
    reference operator[](std::pair<size_type, size_type> xy) noexcept;

    //! Get the number of rows in this raster.
    //! @returns Number of rows
    size_type nrows() const noexcept;

    //! Get the number of columns in this raster.
    //! @returns Number of columns
    size_type ncols() const noexcept;

    //! Get the number of cells in this raster.
    //! @returns Number of cells
    size_type ncells() const noexcept;

    //! Get the beginning iterator/cell of this raster.
    //! @note st::raster iterates in **column-major** form.
    //! @returns st::cell
    iterator begin() noexcept;

    //! Get the beginning (const) iterator/cell of this raster.
    //! @note st::raster iterates in **column-major** form.
    //! @returns const st::cell
    const_iterator begin() const noexcept;

    //! Get the end iterator/cell of this raster.
    //! @note st::raster iterates in **column-major** form.
    //! @returns const st::cell
    iterator end() noexcept;

    //! Get the end (const) iterator/cell of this raster.
    //! @note st::raster iterates in **column-major** form.
    //! @returns const st::cell
    const_iterator end() const noexcept;

    //! Apply a global reducing function to this raster.
    //! @param f A function that takes a st::raster* as the first argument.
    //! @param args Additional arguments passed to `f`.
    //! @returns The return of `f`.
    template<typename Functor, typename... Args>
    auto apply(Functor&& f, Args&&... args)
    {
        return f(*this, std::forward<Args>(args)...);
    }

    //! Apply a local function to this raster.
    //! @param f A function that takes a st::cell as its only argument.
    //! @note If you require a return from this function, currently it's
    //! possible via a static variable within the context of `f`.
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
