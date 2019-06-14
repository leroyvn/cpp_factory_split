#ifndef FACTORY_SPLIT_ANIMAL_H
#define FACTORY_SPLIT_ANIMAL_H

#include <factory/Factory.h>

struct Animal : Factory<Animal, int> {
    Animal(Key) {}
    virtual void makeNoise() = 0;
    virtual ~Animal() = default;
};

#endif //FACTORY_SPLIT_ANIMAL_H
