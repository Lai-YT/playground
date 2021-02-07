#include "./animal.h"

Animal::Animal(std::string const & name, double const weight, bool const fly_ability)
  :name(name)
  ,weight(weight)
  ,fly_ability(fly_ability)
{
  // std::cout << "Animal constructor called" << '\n';
}

Animal::Animal(Animal const & other)
  :name(other.name)
  ,weight(other.weight)
  ,fly_ability(other.fly_ability)
  ,friend_list(other.friend_list)
{
  // std::cout << "Animal copy constructor called" << '\n';
}

Animal::Animal(Animal && other)
  :name(other.name)
  ,weight(other.weight)
  ,fly_ability(other.fly_ability)
  ,friend_list(std::move(other.friend_list))
{
  // std::cout << "Animal move constructor called" << '\n';
}

Animal::~Animal() {
  // std::cout << "Animal destructor called" << '\n';
}

Animal & Animal::operator = (Animal const & other) {
  if (&other != this) {
    this->name = other.name;
    this->weight = other.weight;
    this->fly_ability = other.fly_ability;
    this->friend_list = other.friend_list;
  }
  // std::cout << "Animal copy assignment called" << '\n';
  return *this;
}

Animal & Animal::operator = (Animal && other) {
  this->name = other.name;
  this->weight = other.weight;
  this->fly_ability = other.fly_ability;
  this->friend_list = std::move(other.friend_list);
  // std::cout << "Animal move assignment called" << '\n';
  return *this;
}

void Animal::make_friend_with(std::shared_ptr<Animal> other) {
  this->friend_list.push_back(other);
}

std::string Animal::get_name() const {
  return this->name;
}

double Animal::get_weight() const {
  return this->weight;
}

std::vector<std::string> Animal::get_friend_name_list() {
  std::vector<std::string> friend_name_list;
  // get each friend's name
  for (auto & ani : this->friend_list) {
    friend_name_list.push_back(ani->get_name());
  }
  return friend_name_list;
}

bool Animal::is_faster_than(Animal const & other) const {
  return this->get_speed() > other.get_speed();
}

bool Animal::can_fly() const {
  return fly_ability;
}
