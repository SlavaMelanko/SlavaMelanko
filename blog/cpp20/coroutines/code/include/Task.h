#pragma once

#include "Awaiter.h"
#include "Promise.h"

#include <utility>

namespace coro {

template <typename T, typename PromiseType = Promise<T>,
          template <typename> class AwaiterType = Awaiter>
class Task {
public:
  struct promise_type : PromiseType {
    using PromiseType::PromiseType; // inherit the constructor

    auto get_return_object() {
      return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
    }
  };

  using value_type = typename promise_type::value_type;
  using coro_handle = std::coroutine_handle<promise_type>;

  Task() noexcept = default;
  explicit Task(coro_handle handle) noexcept : m_handle{handle} {}

  ~Task() noexcept { reset(); }

  Task(const Task &) = delete;
  Task &operator=(const Task &) = delete;

  Task(Task &&other) noexcept
      : m_handle{std::exchange(other.m_handle, nullptr)} {}

  Task &operator=(Task &&other) noexcept {
    if (&other != this) {
      reset();
      m_handle = std::exchange(other.m_handle, nullptr);
    }

    return *this;
  }

  value_type result() { return m_handle.promise().result(); }

  void resume() {
    if (m_handle) {
      m_handle.resume();
    }
  }

  operator bool() const { return m_handle && !m_handle.done(); }

  auto operator co_await() const &noexcept {
    return Awaiter<promise_type>{m_handle};
  }

private:
  void reset() noexcept(noexcept(m_handle.destroy())) {
    if (m_handle) {
      m_handle.destroy();
    }
  }

  coro_handle m_handle;
};

} // namespace coro
