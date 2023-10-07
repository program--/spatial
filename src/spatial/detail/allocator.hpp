// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstddef>
#include <memory>

namespace st {
namespace detail {

template<typename Tp>
struct virtual_allocator
{
    using value_type      = Tp;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    virtual ~virtual_allocator() noexcept {};
    virtual Tp*  allocate(size_type n)          = 0;
    virtual void deallocate(Tp* p, size_type n) = 0;
};

namespace alloc {

template<typename Tp>
class stl : public st::detail::virtual_allocator<Tp>
{
    using traits = std::allocator_traits<std::allocator<Tp>>;

  public:
    using value_type = Tp;
    using pointer    = typename traits::pointer;
    using typename virtual_allocator<Tp>::difference_type;
    using typename virtual_allocator<Tp>::size_type;

    stl() noexcept           = default;
    ~stl() noexcept override = default;

    pointer allocate(size_type n) override
    {
        return traits::allocate(alloc_, n);
    }

    void deallocate(pointer p, size_type n) override
    {
        return traits::deallocate(alloc_, static_cast<pointer>(p), n);
    }

  private:
    std::allocator<value_type> alloc_;
};

} // namespace alloc

} // namespace detail
} // namespace st
