#ifndef DOG_H
#define DOG_H

#include "./animal.h"

class Dog : public Animal {
public:
  // let generator handle the exception
  static std::shared_ptr<Dog>
    dog_generator(std::string const & name, double const weight);
  Dog(std::string const & name, double const weight);
  Dog(Dog const & other);
  Dog(Dog && other);
  ~Dog() override;
  Dog & operator = (Dog const & other);
  Dog & operator = (Dog && other);
  double get_speed() const override;

};

#endif /* end of include guard: DOG_H */
