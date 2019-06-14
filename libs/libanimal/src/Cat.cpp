#include <iostream>
#include <animal/Animal.h>

class Cat : public Animal {
  public:
    Cat(ARGS i) : Animal(i), m_i(i) {}

    void makeNoise() override { std::cerr << "Cat: " << m_i << "\n"; }

  private:
    int m_i;
};

// Register this animal
ObjectProvider<Cat, Animal> animal_cat("Cat");
