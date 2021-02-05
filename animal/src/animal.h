#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
#include <string>
#include <iostream> // for constructor testing
#include <memory> // for smart pointer

class Animal {
public:
  // base class constructor
  Animal(std::string const & name, double const weight, bool const fly_ability);

  // base class copy constructor
  Animal(Animal const & other);

  // base class move constructor
  Animal(Animal && other);

  // base class destructor
  virtual ~Animal();

  // base class copy assignment
  Animal & operator = (Animal const & other);

  // base class move assignment
  Animal & operator = (Animal && other);

  // add in friend_list
  void make_friend_with(std::shared_ptr<Animal> other);

  // return name of the animal
  std::string get_name() const;

  // return weight of the animal
  double get_weight() const;

  // return a vector with each friend's name
  std::vector<std::string> get_friend_name_list();

  // derived class should implement with there own speed formula
  double virtual get_speed() const = 0;

  // return true if has a fater speed than other
  bool is_faster_than(Animal const & other) const;

  // true if the animal can fly
  bool can_fly() const;

protected:
  std::string name;
  double weight;
  std::vector<std::shared_ptr<Animal>> friend_list;
  bool fly_ability;

};

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

#endif /* end of include guard: ANIMAL_H */
