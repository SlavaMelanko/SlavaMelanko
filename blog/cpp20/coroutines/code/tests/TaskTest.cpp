#include <gtest/gtest.h>

#include <coroutine>

template <typename Promise> class Awaiter {
public:
  explicit Awaiter(std::coroutine_handle<Promise> handle) : m_handle{handle} {}

  // Tells that is an expression is ready.
  bool await_ready() const noexcept { return !m_handle || m_handle.done(); }

  // Schedules the coroutine for resumption (or destruction) at some point in
  // the future.
  auto await_suspend(std::coroutine_handle<> continuation) noexcept {
    return m_handle;
  }

  // Returns the value that becomes the result of the `co_await` expression.
  // The `await_resume` can also throw an exception in which case the exception
  // propagates out of the `co_await` expression.
  decltype(auto) await_resume() noexcept { return m_handle.promise().result(); }

private:
  std::coroutine_handle<Promise> m_handle;
};

template <typename T> class Task {
public:
  struct promise_type {
    // Tells the compiler how do you want to construct the coroutine.
    auto get_return_object() {
      return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
      // `from_promise` allows reconstructing the coroutine handle from a
      // reference to the coroutine's promise object.
    }

    // First suspension point that tells compiler how we want to suspend the
    // execution.
    std::suspend_always initial_suspend() const noexcept { return {}; }
    std::suspend_always final_suspend() const noexcept { return {}; }

    // What if an exception happens inside coroutine? We should tell
    // how to handle it. Exception free for now. For simplicity.
    void unhandled_exception() const {}

    template <typename T> void return_value(T &&value) noexcept {
      m_value = std::forward<T>(value);
    }

    auto result() const noexcept { return m_value; }

  private:
    T m_value{-1};
  };

  explicit Task(std::coroutine_handle<promise_type> handle) noexcept
      : m_handle{handle} {}

  // Destroys the coroutine frame, calling the destructors of any in-scope
  // variables and freeing memory used by the coroutine frame.
  ~Task() noexcept {
    if (m_handle) {
      m_handle.destroy();
    }
  }

  // Returns the result of the coroutine execution.
  T result() { return m_handle.promise().result(); }

  // Reactivates a suspended coroutine at the resume point.
  void resume() {
    if (m_handle) {
      m_handle.resume();
    }
  }

  explicit operator bool() const { return m_handle && !m_handle.done(); }

  auto operator co_await() const { return Awaiter<promise_type>{m_handle}; }

private:
  // Coroutine handle represents a non-owning handle to the coroutine frame and
  // can be used to resume execution of the coroutine or to destroy the
  // coroutine frame. It can also be used to get access to the coroutine’s
  // promise object.
  std::coroutine_handle<promise_type> m_handle;
};

#if 0
TEST(TaskTest, FirstTask) {
  auto square = [](const int val) -> Task<int> { co_return(val * val); };
  auto task = square(2);
  EXPECT_EQ(task.result(), 4);
}

// error: Expected equality of these values:
//   task.result()
//     Which is : -572662307
//   0
#endif

#if 0
TEST(TaskTest, FirstTask) {
  // std::suspend_never final_suspend() -> std::suspend_always final_suspend()
  auto square = [](const int val) -> Task<int> { co_return(val * val); };
  auto task = square(2);
  EXPECT_EQ(task.result(), 4);
}
#endif

Task<int> bar(const int val) { co_return(val * val); }
Task<int> foo(const int val) { co_return co_await bar(val); }

TEST(TaskTest, CoroInCoro) {
  auto task = foo(3);
  while (task)
    task.resume();
  EXPECT_EQ(task.result(), 9);
}

// >_ error C2039: 'await_resume': is not a member of 'Task<int>'
