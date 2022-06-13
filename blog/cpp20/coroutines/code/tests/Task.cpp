#include <gtest/gtest.h>

#include <Task.h>

coro::Task<int> Square(int val) { co_return(val * val); }

TEST(TaskTest, InitialState) {
  coro::Task<void> taskVoid;
  EXPECT_FALSE(taskVoid);
  coro::Task<int> taskInt;
  EXPECT_FALSE(taskInt);
}

TEST(TaskTest, ReturnVoid) {
  auto task = []() -> coro::Task<void> { co_return; }();
  EXPECT_TRUE(task);
  if (task) {
    task.resume();
  }
  EXPECT_FALSE(task);
}

TEST(TaskTest, ReturnInt) {
  auto task = Square(2);
  EXPECT_TRUE(task);
  if (task) {
    task.resume();
  }
  EXPECT_FALSE(task);
  EXPECT_EQ(task.result(), 4);
}
