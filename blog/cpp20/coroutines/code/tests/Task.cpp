#include <gtest/gtest.h>

#include <Task.h>

coro::Task<int> Square(int val) {
  co_return(val * val);
}

TEST(TaskTest, Square)
{
  auto task = Square(2);
  EXPECT_TRUE(task);
  if (task) {
    task.resume();
  }
  EXPECT_EQ(task.result(), 4);
}
