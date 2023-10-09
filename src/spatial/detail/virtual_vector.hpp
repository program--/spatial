// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <spatial/detail/types.hpp>
#include <spatial/detail/virtual_allocator.hpp>

namespace st {
namespace detail {

template<typename Tp>
struct virtual_vector
{
    using size_type       = types::size_type;
    using difference_type = types::difference_type;
    using value_type      = Tp;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using iterator        = pointer;
    using const_iterator  = const_pointer;
    using allocator_type  = std::unique_ptr<virtual_allocator<value_type>>;
    using alloc_ref       = allocator_type&;
    using const_alloc_ref = const allocator_type&;

    constexpr virtual_vector(allocator_type alloc = nullptr) noexcept
      : alloc_(
          alloc != nullptr ? std::move(alloc)
                           : std::make_unique<detail::alloc::stl<value_type>>()
        )
      , capacity_(0)
      , size_(0)
      , data_(nullptr){};

    constexpr virtual_vector(
      size_type      size,
      allocator_type alloc = nullptr
    ) noexcept
      : virtual_vector(alloc)
      , capacity_(size)
      , size_(0)
      , data_(alloc_->allocate(size)){};

    constexpr virtual_vector(std::initializer_list<value_type> x) noexcept
      : virtual_vector(x.size())
    {
        for (auto e = begin(), v = x.begin(); v != x.end(); e++, v++)
            *e = *v;
    }

    ~virtual_vector() noexcept
    {
        if (data_ != nullptr) {
            alloc_->deallocate(data_, capacity_);
        }
    }

    constexpr alloc_ref       allocator() noexcept { return alloc_; }
    constexpr const_alloc_ref allocator() const noexcept { return alloc_; }
    constexpr reference       at(size_type n) { return data_[n]; }
    constexpr const_reference at(size_type n) const { return data_[n]; }
    constexpr reference       front() noexcept { return *begin(); }
    constexpr const_reference front() const noexcept { return *begin(); }
    constexpr reference       back() noexcept { return *end(); }
    constexpr const_reference back() const noexcept { return *end(); }
    constexpr iterator        begin() noexcept { return data_; }
    constexpr const_iterator  begin() const noexcept { return data_; }
    constexpr iterator        end() noexcept { return data_ + size_; }
    constexpr const_iterator  end() const noexcept { return data_ + size_; }
    constexpr size_type       size() const noexcept { return size_; }
    constexpr size_type       max_size() const noexcept { return -1; }
    constexpr size_type       capacity() const noexcept { return capacity_; }
    constexpr reference operator[](size_type n) noexcept { return data_[n]; }
    constexpr const_reference operator[](size_type n) const noexcept
    {
        return data_[n];
    }

    constexpr void push_back(const value_type& x)
    {
        if (size_ <= capacity_) {
            pointer tmp = alloc_->allocate(capacity_ * 2);
            for (pointer x = data_, y = tmp; x != data_ + size_; ++x, ++y)
                *y = std::move(*x);
            data_     = tmp;
            capacity_ = capacity_ * 2;
        }

        data_[size_++] = x;
    }

    constexpr void push_back(value_type&& x)
    {
        if (size_ <= capacity_) {
            pointer tmp = alloc_->allocate(capacity_ * 2);
            for (pointer x = data_, y = tmp; x != data_ + size_; ++x, ++y)
                *y = std::move(*x);
            data_     = tmp;
            capacity_ = capacity_ * 2;
        }

        data_[size_++] = std::move(x);
    }

    constexpr void erase() noexcept
    {
        for (auto& ele : *this)
            ele = value_type{};
        size_ = 0;
    }

    template<typename... Args>
    constexpr void emplace_back(Args&&... args)
    {
        push_back(value_type{ std::forward<Args>(args)... });
    }

    constexpr void swap(virtual_vector& other) noexcept
    {
        virtual_vector tmp{ std::move(alloc_) };
        tmp.capacity_   = std::move(capacity_);
        tmp.size_       = std::move(size_);
        tmp.data_       = std::move(data_);

        alloc_          = std::move(other.alloc_);
        capacity_       = std::move(other.capacity_);
        size_           = std::move(other.size_);
        data_           = std::move(other.data_);

        other.alloc_    = std::move(tmp.alloc_);
        other.capacity_ = std::move(tmp.capacity_);
        other.size_     = std::move(tmp.size_);
        other.data_     = std::move(tmp.data_);
    }

  private:
    allocator_type alloc_;
    size_type      capacity_;
    size_type      size_;
    pointer        data_;
};

} // namespace detail
} // namespace st
