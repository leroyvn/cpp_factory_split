#include <iostream>
#include <animal/Animal.h>

class Dog : public Animal::Registrar<Dog> {
  public:
    Dog(int x) : m_x(x) {}

    void makeNoise() override { std::cerr << "Dog: " << m_x << "\n"; }

  private:
    int m_x;
};