#include <animal/AnimalFactoryMap.h>

int main() {
    int objectType(99);

    AnimalFactoryIter it = AnimalFactoryMap().find(objectType);

    if (it!=AnimalFactoryMap().end()) {
        Animal *animal = (*it).second(3);
        animal->make_noise();
        delete animal;
    }
}
