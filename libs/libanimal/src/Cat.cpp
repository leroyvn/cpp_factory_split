#include <iostream>
#include <animal/Animal.h>

class Cat : public Animal::Registrar<Cat> {
  public:
    Cat(int x) : m_x(x) {}

    void makeNoise() override { std::cerr << "Cat: " << m_x << "\n"; }

  private:
    int m_x;
};
