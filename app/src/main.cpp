// From http://www.nirfriedman.com/2018/04/29/unforgettable-factory/

#include <animal/Animal.h>

int main() {
    auto x = Animal::make("Dog", 3);
    auto y = Animal::make("Cat", 2);
    x->makeNoise();
    y->makeNoise();
    return 0;
}
