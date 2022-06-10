#pragma once

#if __has_include(<coroutine>)
#include <coroutine>
#elif __has_include(<experimental/coroutine>)
#include <experimental/coroutine>

namespace std {

template<typename Promise = void>
using coroutine_handle = experimental::coroutine_handle<Promise>;

using suspend_always = experimental::suspend_always;
using suspend_never = experimental::suspend_never;

inline constexpr auto noop_coroutine = experimental::noop_coroutine;

} // namesapce std

#else
#error "Your compiler doesn't support coroutines"
#endif
