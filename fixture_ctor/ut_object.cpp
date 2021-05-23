#include "object.hpp"

#include <gtest/gtest.h>


class ObjectTest : public ::testing::Test {
protected:
  ObjectTest()
    :de1_(2)
    ,de2_(3)
    ,de_p1_(new Derived(4))
    ,de_p2_(new Derived(5))
  {}

  virtual ~ObjectTest() noexcept {
    delete de_p1_;
    delete de_p2_;
  }

  const Derived de1_, de2_;
  Base *de_p1_, *de_p2_;
};


TEST_F(ObjectTest, Ctor) {
  ASSERT_EQ(2, de1_.i());
  ASSERT_EQ(3, de2_.i());
}


TEST_F(ObjectTest, Dtor) {
  ASSERT_EQ(4, de_p1_->i());
  ASSERT_EQ(5, de_p2_->i());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
