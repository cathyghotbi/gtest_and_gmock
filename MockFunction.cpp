#include <gtest/gtest.h>
#include <gmock/gmock.h>

//---------------------------------------------------------------------------------------------------------
class FutureTaskIf
{
public:
  virtual void doTheTask() = 0;
};
//---------------------------------------------------------------------------------------------------------
class FutureTask : public FutureTaskIf
{
public:
  FutureTask(std::function<void()> futureTask)
  : m_futureTask(futureTask)
  { 
  }

  void doTheTask()
  {
    m_futureTask(); 
  }
private:
  std::function<void()> m_futureTask;
};
//---------------------------------------------------------------------------------------------------------
class MockFutureTask : public FutureTaskIf
{
public:
  MOCK_METHOD0(doTheTask, void());
};
//---------------------------------------------------------------------------------------------------------
class User
{
public:
  User(std::function<void()> futureTask)
  : m_futureTask(futureTask)
  {
  }

  void userAction()
  {
    m_futureTask();
  }

private:
  std::function<void()> m_futureTask;
};
//---------------------------------------------------------------------------------------------------------
using ::testing::_;
using ::testing::MockFunction;

class UserTest : public ::testing::Test
{
public:
  UserTest()
  {
    m_user.reset(new User(m_mockFutureTask.AsStdFunction()));
  }

protected:
  std::unique_ptr<User> m_user;
  MockFunction<std::function<void()>> m_mockFutureTask;
};

TEST_F(UserTest, testfutureTask)
{
  EXPECT_CALL(m_mockFutureTask, Call());

  m_mockFutureTask.AsStdFunction();
  m_user->userAction();
}
//---------------------------------------------------------------------------------------------------------
int main()
{
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
//---------------------------------------------------------------------------------------------------------
