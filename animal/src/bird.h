#ifndef BIRD_H
#define BIRD_H

#include "./animal.h"

class Bird : public Animal {
public:
  // let generator handle the exception
  static std::shared_ptr<Bird>
    bird_generator(std::string const & name, double const weight, double const wing_width);
  Bird(std::string const & name, double const weight, double const wing_width);
  Bird(Bird const & other);
  Bird(Bird && other);
  ~Bird() override;
  Bird & operator = (Bird const & other);
  Bird & operator = (Bird && other);
  double get_speed() const override;
  double get_wing_width() const;

private:
  /*  bird has a unique data member: wing_width */
  double wing_width;

};

  std::shared_ptr<Bird> Bird::bird_generator(std::string const & name, double const weight, double const wing_width) {
  if (name.empty()) {
    throw std::string("ERROR: NO_NAME");
  }
  if (weight < 20 || weight > 40) {
    throw std::string("ERROR: WEIGHT_OUT_OF_RANGE");
  }
  if (wing_width < 0 || wing_width > 20) {
    throw std::string("ERROR: WING_WIDTH_OUT_OF_RANGE");
  }
  return std::make_shared<Bird>(Bird(name, weight, wing_width));
}

// call constructor of the Animal to initialize base-hold data members
Bird::Bird(std::string const & name, double const weight, double const wing_width)
  :Animal(name, weight, wing_width != 0) // bird can't fly if no wings
  ,wing_width(wing_width)
{
  // std::cout << "Bird constructor called" << '\n';
}


// call copy constructor of Animal to copy base-hold data members
Bird::Bird(Bird const & other)
  :Animal(other)
  ,wing_width(other.wing_width)
{
    // std::cout << "Bird copy constructor called" << '\n';
}

Bird::Bird(Bird && other)
  :Animal(std::move(other))
  ,wing_width(other.wing_width)
{
  // std::cout << "Bird move constructor called" << '\n';
}

Bird::~Bird() {
    // std::cout << "Bird destructor called" << '\n';
}

Bird & Bird::operator = (Bird const & other) {
  if (&other != this) {
    // call assignment operator of Animal to copy base-hold data members
    Animal::operator = (other);
    this->wing_width = other.wing_width;
  }
 // std::cout << "Bird copy assignment called" << '\n';
 return *this;
}

Bird & Bird::operator = (Bird && other) {
  // call assignment operator of Animal to copy base-hold data members
  Animal::operator = (std::move(other));
  this->wing_width = other.wing_width;
  // std::cout << "Bird move assignment called" << '\n';
  return *this;
}

double Bird::get_speed() const {
  // can fly or can't fly
  return (fly_ability) ? (wing_width * 0.1) : (20 / weight);
}

double Bird::get_wing_width() const {
  return this->wing_width;
}

#endif /* end of include guard: BIRD_H */
