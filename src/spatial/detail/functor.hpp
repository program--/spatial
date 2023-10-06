// spatial: a general-purpose geospatial library
//
// Copyright (c) 2023 Justin Singh-Mohudpur <justin@justinsingh.me>
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace spatial {
namespace detail {

template<typename... Fs>
struct functor;

template<typename F, typename... Fs>
struct functor<F, Fs...>
  : public functor<Fs...>
  , public F
{
    using F::operator();
    using functor<Fs...>::operator();

    explicit functor(F f, Fs... fs)
      : F(f)
      , functor<Fs...>(fs...)
    {}
};

template<typename F>
struct functor<F> : public F
{
    using F::operator();
    explicit functor(F f)
      : F(f){};
};

} // namespace detail
} // namespace spatial
