#ifndef FACTORY_SPLIT_ANIMAL_H
#define FACTORY_SPLIT_ANIMAL_H

#include <factory/Factory.h>

struct Animal {
    // Required for self registering animals
    typedef int ARGS;

    /// Returns name of this type.
    static std::string typeName() { return "Animal"; }

    explicit Animal(ARGS i) {}
    virtual void makeNoise() = 0;
    virtual ~Animal() = default;
};

#endif //FACTORY_SPLIT_ANIMAL_H
