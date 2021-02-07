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

#endif /* end of include guard: BIRD_H */
