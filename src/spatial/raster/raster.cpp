// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <spatial/raster/raster.hpp>

#include <cstring>
#include <stdexcept>

namespace st {

#define MOVE_OR_DEFAULT_ALLOC(allocator) \
    (allocator != nullptr                \
       ? std::move(allocator)            \
       : std::make_unique<detail::alloc::stl<raster::value_type>>())

raster::raster(
  const size_type     nrows,
  const size_type     ncols,
  const types::extent ext,
  allocator_type      allocator
)
  : xaxis_(ext.xmin, ext.xmax, ncols)
  , yaxis_(ext.ymin, ext.ymax, nrows)
  , alloc_(MOVE_OR_DEFAULT_ALLOC(allocator))
  , data_(alloc_->allocate(nrows * ncols))
{
    std::memset(data_, 0, sizeof(value_type) * ncells());
};

#undef MOVE_OR_DEFAULT_ALLOC

raster::~raster()
{
    if (data_ != nullptr) {
        alloc_->deallocate(data_, ncells());
    }
};

auto raster::xaxis() const noexcept -> const axis&
{
    return xaxis_;
}

auto raster::yaxis() const noexcept -> const axis&
{
    return yaxis_;
}

auto raster::at(const size_type col, const size_type row) -> reference
{
    if (col >= ncols() || col < 0 || row >= nrows() || row < 0) {
        throw std::out_of_range(
          "Index (" + std::to_string(col) + ", " + std::to_string(row) +
          ") is out of range of extent (" + std::to_string(ncols()) + ", " +
          std::to_string(nrows()) + ")"
        );
    }

    return cell{ &data_[row + (col * nrows())], row, col, nrows(), ncols() };
}

auto raster::operator[](std::pair<size_type, size_type> xy) noexcept
  -> reference
{
    const size_type& col = xy.first;
    const size_type& row = xy.second;
    return cell{ &data_[row + (col * nrows())], row, col, nrows(), ncols() };
}

auto raster::nrows() const noexcept -> size_type
{
    return yaxis_.size();
}

auto raster::ncols() const noexcept -> size_type
{
    return xaxis_.size();
}

auto raster::ncells() const noexcept -> size_type
{
    return nrows() * ncols();
}

auto raster::begin() noexcept -> iterator
{
    return cell{ data_, 0, 0, nrows(), ncols() };
}

auto raster::begin() const noexcept -> const_iterator
{
    return cell{ data_, 0, 0, nrows(), ncols() };
}

auto raster::end() noexcept -> iterator
{
    return cell{ data_ + ncells(), nrows() - 1, ncols(), nrows(), ncols() };
}

auto raster::end() const noexcept -> const_iterator
{
    return cell{ data_ + ncells(), nrows() - 1, ncols(), nrows(), ncols() };
}

} // namespace st
