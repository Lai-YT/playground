#include <gtest/gtest.h>

#include "my_vector.hpp"


// See what's printed in the console. 

TEST(MyVectorTest, Constructor) {
  MyVector<int> vec = {0, 1, 2, 3};
  for (size_t i = 0; i < vec.size(); i++) {
    ASSERT_EQ(i, vec.at(i));
  }
}

TEST(MyVectorTest, Operator) {
  MyVector<int> vec;
  vec = {0, 1, 2, 3};
  for (size_t i = 0; i < vec.size(); i++) {
    ASSERT_EQ(i, vec.at(i));
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
