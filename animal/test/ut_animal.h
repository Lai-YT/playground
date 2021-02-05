#include "../src/animal.h"
#include "../src/dog.h"
#include "../src/bird.h"

class AnimalTest : public ::testing::Test {
protected:
  void SetUp() override {
    puppy = std::make_shared<Dog>(Dog("Puppy", 50));
    birdy = std::make_shared<Bird>(Bird("Birdy", 30, 10));
  }
  std::shared_ptr<Dog> puppy;
  std::shared_ptr<Bird> birdy;
};

TEST_F(AnimalTest, Get_name) {
  ASSERT_EQ("Puppy", puppy->get_name());
}

TEST_F(AnimalTest, Get_weight) {
  ASSERT_NEAR(50, puppy->get_weight(), 0.001);
  ASSERT_NEAR(30, birdy->get_weight(), 0.001);
}

TEST_F(AnimalTest, Get_friend_name_list) {
  puppy->make_friend_with(birdy);
  std::vector<std::string> puppy_friends = puppy->get_friend_name_list();

  ASSERT_EQ(1, puppy_friends.size());
  ASSERT_EQ("Birdy", puppy_friends.at(0));
}

TEST_F(AnimalTest, Get_speed) {
  ASSERT_NEAR(0.8, puppy->get_speed(), 0.001);
  ASSERT_NEAR(1, birdy->get_speed(), 0.001);
}

TEST_F(AnimalTest, Is_faster_than) {
  ASSERT_TRUE(birdy->is_faster_than(*puppy));
}

TEST_F(AnimalTest, Copy_constructor) {
  Dog luppy = *puppy;
  Bird bibby = *birdy;
  ASSERT_EQ("Puppy", luppy.get_name());
  ASSERT_EQ("Birdy", bibby.get_name());
  ASSERT_NEAR(10, bibby.get_wing_width(), 0.001);
}

TEST_F(AnimalTest, Move_constructor) {
  // Dog move constructor
  Dog teddy = Dog("Charlie", 40);
  ASSERT_EQ("Charlie", teddy.get_name());
  ASSERT_NEAR(40, teddy.get_weight(), 0.001);
  // Bird move constructor
  Bird bobby = Bird("Bibby", 20, 5);
  ASSERT_EQ("Bibby", bobby.get_name());
  ASSERT_NEAR(5, bobby.get_wing_width(), 0.001);
}

TEST_F(AnimalTest, Copy_assignment) {
  Dog luppy("Luppy", 40);
  Bird bibby("Bibby", 20, 5);
  // luppy and bibby is successfully constructed
  ASSERT_EQ("Luppy", luppy.get_name());
  ASSERT_EQ("Bibby", bibby.get_name());
  ASSERT_NEAR(5, bibby.get_wing_width(), 0.001);
  // luppy and bibby is successfully assigned
  luppy = *puppy;
  bibby = *birdy;
  ASSERT_EQ("Puppy", luppy.get_name());
  ASSERT_EQ("Birdy", bibby.get_name());
  ASSERT_NEAR(10, bibby.get_wing_width(), 0.001);
  // puppy and birdy not modified
  ASSERT_EQ("Puppy", puppy->get_name());
  ASSERT_EQ("Birdy", birdy->get_name());
  ASSERT_NEAR(10, birdy->get_wing_width(), 0.001);
}

TEST_F(AnimalTest, Move_assignment) {
  // Dog move assignment
  Dog teddy("Teddy", 45);
  ASSERT_EQ("Teddy", teddy.get_name());
  ASSERT_NEAR(45, teddy.get_weight(), 0.001);
  teddy = Dog("Charlie", 40);
  ASSERT_EQ("Charlie", teddy.get_name());
  ASSERT_NEAR(40, teddy.get_weight(), 0.001);
  // Bird move assignment
  Bird bobby("Bobby", 25, 15);
  ASSERT_EQ("Bobby", bobby.get_name());
  ASSERT_NEAR(15, bobby.get_wing_width(), 0.001);
  bobby = Bird("Bibby", 20, 5);
  ASSERT_EQ("Bibby", bobby.get_name());
  ASSERT_NEAR(5, bobby.get_wing_width(), 0.001);
}

TEST_F(AnimalTest, Can_fly) {
  Bird bibby("Bibby", 20, 0);
  ASSERT_FALSE(puppy->can_fly());
  ASSERT_TRUE(birdy->can_fly());
  ASSERT_FALSE(bibby.can_fly());
}

TEST_F(AnimalTest, Generator) {
  auto teddy = Dog::dog_generator("Teddy", 40);
  ASSERT_EQ("Teddy", teddy->get_name());
  ASSERT_NEAR(40, teddy->get_weight(), 0.001);

  auto bobby = Bird::bird_generator("Bobby", 25, 15);
  ASSERT_EQ("Bobby", bobby->get_name());
  ASSERT_NEAR(15, bobby->get_wing_width(), 0.001);
}

TEST_F(AnimalTest, Generator_Exception) {
  ASSERT_THROW(Dog::dog_generator("", 40), std::string);
  ASSERT_THROW(Dog::dog_generator("Teddy", 39), std::string);

  ASSERT_THROW(Bird::bird_generator("", 20, 10), std::string);
  ASSERT_THROW(Bird::bird_generator("Bobby", 19, 10), std::string);
  ASSERT_THROW(Bird::bird_generator("Bobby", 20, 21), std::string);
  ASSERT_THROW(Bird::bird_generator("Bobby", 20, -1), std::string);
}


TEST_F(AnimalTest, Friend_list_so_smart) {
  Dog teddy("Teddy", 40);
  {
    auto bob = std::make_shared<Bird>(Bird("Bob", 20, 10));
    teddy.make_friend_with(bob);
    auto teddy_friend_name_list = teddy.get_friend_name_list();
    ASSERT_EQ(1, teddy_friend_name_list.size());
    ASSERT_EQ("Bob", teddy_friend_name_list.at(0));
  }
  auto teddy_friend_name_list = teddy.get_friend_name_list();
  ASSERT_EQ(1, teddy_friend_name_list.size());
  ASSERT_EQ("Bob", teddy_friend_name_list.at(0));
}
