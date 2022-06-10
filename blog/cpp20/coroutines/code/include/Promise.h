#pragma once

#include <exception>
#include <variant>

#include "Coroutine.h"

namespace coro {

namespace detail {

template <typename T> class PromiseImpl {
public:
  using value_type = T;

  template <typename U>
  void return_value(U &&value) noexcept(
      std::is_nothrow_constructible_v<value_type,
                                      decltype(std::forward<U>(value))>) {
    m_result.template emplace<1>(std::forward<U>(value));
  }

  void unhandled_exception() noexcept {
    m_result.template emplace<2>(std::current_exception());
  }

  value_type &&result() {
    if (m_result.index() == 2) {
      std::rethrow_exception(std::get<2>(m_result));
    }
    return std::move(std::get<1>(m_result));
  }

private:
  std::variant<std::monostate, T, std::exception_ptr> m_result;
};

template <> class PromiseImpl<void> {
public:
  using value_type = void;

  void return_void() const noexcept {}

  void result() {
    if (m_exception) {
      std::rethrow_exception(m_exception);
    }
  }

  void unhandled_exception() noexcept {
    m_exception = std::current_exception();
  }

private:
  std::exception_ptr m_exception;
};

} // namespace detail

template <typename T> class Promise : public detail::PromiseImpl<T> {
public:
  struct final_awaiter {
    bool await_ready() const noexcept { return false; }

    template <typename Promise>
    std::coroutine_handle<> await_suspend(std::coroutine_handle<Promise> coro) noexcept {
      if (coro.promise().m_continuation) {
        return coro.promise().m_continuation;
      }

      return std::noop_coroutine();
    }

    void await_resume() noexcept {}
  };

  std::suspend_always initial_suspend() noexcept { return {}; }
  final_awaiter final_suspend() noexcept { return {}; }

  void set_continuation(std::coroutine_handle<> continuation) noexcept {
    m_continuation = continuation;
  }

private:
  std::coroutine_handle<> m_continuation;
};

} // namespace coro
