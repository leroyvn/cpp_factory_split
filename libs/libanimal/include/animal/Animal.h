//
// Created by Vincent Leroy on 2019-06-13.
//

#ifndef FACTORY_SPLIT_ANIMAL_H
#define FACTORY_SPLIT_ANIMAL_H

#include <factory/Factory.h>

struct Animal : Factory<Animal, int> {
    Animal(Key) {}
    virtual void makeNoise() = 0;
};

#endif //FACTORY_SPLIT_ANIMAL_H
