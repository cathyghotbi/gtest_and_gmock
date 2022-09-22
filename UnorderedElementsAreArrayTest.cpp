#include <gtest/gtest.h>
#include <gmock/gmock.h> // UnorderedElementsAreArray
//---------------------------------------------------------------------------------------------------------
using ::testing::_;

TEST(UnorderedElementsAreArrayTest, vectorTest)
{
  const int actual[] = {1, 2, 3};

  std::vector<int> expected;
  expected.push_back(1);
  expected.push_back(2);
  expected.push_back(3);

  EXPECT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));

  expected.push_back(4);

  EXPECT_THAT(actual, ::testing::Not(::testing::UnorderedElementsAreArray(expected)));
}

TEST(UnorderedElementsAreArrayNotSameOrderTest, vectorTest)
{
  const int actual[] = {1, 2, 5, 4, 3};

  std::vector<int> expected;
  expected.push_back(1);
  expected.push_back(2);
  expected.push_back(3);
  expected.push_back(4);
  expected.push_back(5);

  EXPECT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));
}
//---------------------------------------------------------------------------------------------------------
int main()
{
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
//---------------------------------------------------------------------------------------------------------
