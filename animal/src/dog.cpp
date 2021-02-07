#include "./dog.h"

std::shared_ptr<Dog> Dog::dog_generator(std::string const & name, double const weight) {
  if (name.empty()) {
    throw std::string("ERROR: NO_NAME");
  }
  if (weight < 40 || weight > 60) {
    throw std::string("ERROR: WEIGHT_OUT_OF_RANGE");
  }
  return std::make_shared<Dog>(Dog(name, weight));
}
// call constructor of the Animal to initialize base-hold data members
Dog::Dog(std::string const & name, double const weight)
  :Animal(name, weight, false)
{
  // std::cout << "Dog constructor called" << '\n';
}
// call copy constructor of Animal to copy base-hold data members
Dog::Dog(Dog const & other)
  :Animal(other)
{
  // std::cout << "Dog copy constructor called" << '\n';
}

Dog::Dog(Dog && other)
  :Animal(std::move(other))
{
  // std::cout << "Dog move constructor called" << '\n';
}

Dog::~Dog() {
  // std::cout << "Dog destructor called" << '\n';
}

Dog & Dog::operator = (Dog const & other) {
  if (&other != this) {
    // call assignment operator of Animal to copy base-hold data members
    Animal::operator = (other);
  }
  // std::cout << "Dog copy assignment called" << '\n';
  return *this;
}

Dog & Dog::operator = (Dog && other) {
  // call assignment operator of Animal to copy base-hold data members
  Animal::operator = (std::move(other));
  // std::cout << "Dog move assignment called" << '\n';
  return *this;
}

double Dog::get_speed() const {
  return 40 / this->weight;
}
