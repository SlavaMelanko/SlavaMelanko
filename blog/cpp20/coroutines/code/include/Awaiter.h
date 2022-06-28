#pragma once

#include "Coroutine.h"

namespace coro {

template <typename Promise> class Awaiter {
public:
  explicit Awaiter(std::coroutine_handle<Promise> handle)
      : m_handle{handle} {}

  bool await_ready() const noexcept { return !m_handle || m_handle.done(); }

  template <typename P>
  auto await_suspend(std::coroutine_handle<P> continuation) noexcept {
    m_handle.promise().set_continuation(continuation);
    return m_handle;
  }

  decltype(auto) await_resume() { return m_handle.promise().result(); }

private:
  std::coroutine_handle<Promise> m_handle;
};

} // namespace coro
