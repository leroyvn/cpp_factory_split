#include <animal/Animal.h>

int main() {
    auto x = Factory<Animal>::create("Dog", 3);
    auto y = Factory<Animal>::create("Cat", 2);
    x->makeNoise();
    y->makeNoise();
    return 0;
}
