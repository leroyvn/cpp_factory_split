#include <iostream>
#include <animal/Animal.h>

class Dog : public Animal {
  public:
    Dog(ARGS i) : Animal(i), m_i(i) {}

    void makeNoise() override { std::cerr << "Dog: " << m_i << "\n"; }

  private:
    int m_i;
};

// Register this animal
ObjectProvider<Dog, Animal> animal_dog("Dog");
