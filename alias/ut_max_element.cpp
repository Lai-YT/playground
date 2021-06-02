#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <vector>

// Try using different ways to setup an alias.
// The deduce way is lot more neat.

class AliasTest : public ::testing::Test {
protected:
  void SetUp() override {
    v_ = {1, 9, 2, 8, 3, 7, 4, 6, 5};
  }

  std::vector<int> v_;
};


namespace use {

  using IntComp = std::function<bool(int, int)>;
  using IntItr  = std::vector<int>::iterator;

  bool Less(int r, int l) {
    return r < l;
  }

  TEST_F(AliasTest, Use) {
    IntItr max_int = std::max_element<IntItr, IntComp>(v_.begin(), v_.end(), Less);
    ASSERT_EQ(9, *max_int);
  }

}  // namespace use


namespace type_define {

  typedef std::function<bool(int, int)> IntComp;
  typedef std::vector<int>::iterator    IntItr;

  bool Less(int r, int l) {
    return r < l;
  }

  TEST_F(AliasTest, Typedefine) {
    IntItr max_int = std::max_element<IntItr, IntComp>(v_.begin(), v_.end(), Less);

    ASSERT_EQ(9, *max_int);
  }

}  // namespace type_define


namespace pure {

  using IntComp = bool(*)(int, int);

  bool Less(int r, int l) {
    return r < l;
  }

  TEST_F(AliasTest, Pure) {
    std::vector<int>::iterator max_int
      = std::max_element<std::vector<int>::iterator, IntComp>(v_.begin(), v_.end(), Less);

    ASSERT_EQ(9, *max_int);
  }

}  // namespace pure


namespace deduce {

  auto less = [](int r, int l) -> bool {
                return r < l;
              };

  TEST_F(AliasTest, deduce) {
    // One can just place the lambda expression as the argument.
    auto max_int = std::max_element(v_.begin(), v_.end(), less);

    ASSERT_EQ(9, *max_int);
  }

}  // namespace deduce


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
