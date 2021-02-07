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

#endif /* end of include guard: ANIMAL_H */
