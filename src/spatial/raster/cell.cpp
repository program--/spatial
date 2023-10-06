// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <spatial/raster/cell.hpp>

namespace spatial {

constexpr auto invalid_value = static_cast<cell::size_type>(-1);

cell::cell()
  : row_(invalid_value)
  , col_(invalid_value)
  , nrows_(invalid_value)
  , ncols_(invalid_value)
  , cell_(nullptr){};

cell cell::invalid =
  cell{ nullptr, invalid_value, invalid_value, invalid_value, invalid_value };

cell::cell(
  pointer   ptr,
  size_type row,
  size_type col,
  size_type nrows,
  size_type ncols
)
  : row_(row)
  , col_(col)
  , nrows_(nrows)
  , ncols_(ncols)
  , cell_(ptr){};

cell& cell::operator=(value_type rhs) noexcept
{
    *cell_ = rhs;
    return *this;
}

auto cell::operator*() noexcept -> reference
{
    return *cell_;
}

auto cell::operator*() const noexcept -> const_reference
{
    return *cell_;
}

auto cell::operator->() noexcept -> pointer
{
    return cell_;
}

auto cell::operator->() const noexcept -> const_pointer
{
    return cell_;
}

auto cell::lshift() const noexcept -> difference_type
{
    return -nrows_;
}

auto cell::rshift() const noexcept -> difference_type
{
    return -lshift();
}

auto cell::ushift() const noexcept -> difference_type
{
    return 1;
}

auto cell::dshift() const noexcept -> difference_type
{
    return -ushift();
}

cell cell::left() const noexcept
{
    return col_ == 0 ? cell{}
                     : cell{ cell_ + lshift(), row_, col_ - 1, nrows_, ncols_ };
}

cell cell::right() const noexcept
{
    return col_ + 1 >= ncols_
             ? cell{}
             : cell{ cell_ + rshift(), row_, col_ + 1, nrows_, ncols_ };
}

cell cell::top() const noexcept
{
    return row_ + 1 >= nrows_
             ? cell{}
             : cell{ cell_ + ushift(), row_ + 1, col_, nrows_, ncols_ };
}

cell cell::bottom() const noexcept
{
    return row_ == 0 ? cell{}
                     : cell{ cell_ + dshift(), row_ - 1, col_, nrows_, ncols_ };
}

cell cell::top_left() const noexcept
{
    return row_ + 1 >= nrows_ || col_ == 0 ? cell{}
                                           : cell{ cell_ + ushift() + lshift(),
                                                   row_ + 1,
                                                   col_ - 1,
                                                   nrows_,
                                                   ncols_ };
}

cell cell::top_right() const noexcept
{
    return row_ + 1 >= nrows_ || col_ + 1 >= ncols_
             ? cell{}
             : cell{ cell_ + ushift() + rshift(),
                     row_ + 1,
                     col_ + 1,
                     nrows_,
                     ncols_ };
}

cell cell::bottom_left() const noexcept
{
    return row_ == 0 || col_ == 0 ? cell{}
                                  : cell{ cell_ + dshift() + lshift(),
                                          row_ - 1,
                                          col_ - 1,
                                          nrows_,
                                          ncols_ };
}

cell cell::bottom_right() const noexcept
{
    return row_ == 0 || col_ + 1 >= ncols_ ? cell{}
                                           : cell{ cell_ + dshift() + rshift(),
                                                   row_ - 1,
                                                   col_ + 1,
                                                   nrows_,
                                                   ncols_ };
}

auto cell::index() const noexcept -> std::pair<size_type, size_type>
{
    return { col_, row_ };
}

cell& cell::operator++() noexcept
{
    cell_++;
    col_++;
    return *this;
}

cell cell::operator++(int) noexcept
{
    return left();
}

cell& cell::operator--() noexcept
{
    cell_--;
    col_--;
    return *this;
}

cell cell::operator--(int) noexcept
{
    return right();
}

bool cell::operator==(const cell& rhs) const noexcept
{
    return cell_ == rhs.cell_;
}

bool cell::operator!=(const cell& rhs) const noexcept
{
    return cell_ != rhs.cell_;
}

bool cell::operator==(value_type rhs) const noexcept
{
    return *cell_ == rhs;
}

bool cell::operator!=(value_type rhs) const noexcept
{
    return *cell_ != rhs;
}

cell::operator pointer() noexcept
{
    return cell_;
}

cell::operator const_pointer() const noexcept
{
    return cell_;
}

} // namespace spatial
