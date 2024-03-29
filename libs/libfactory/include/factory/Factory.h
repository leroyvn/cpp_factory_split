#ifndef FACTORY_SPLIT_FACTORY_H
#define FACTORY_SPLIT_FACTORY_H

#include <string>
#include <unordered_map>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char *name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    std::unique_ptr<char, void (*)(void *)> res{
        abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};

    return (status == 0) ? res.get() : name;
}

template<class Base, class... Args>
class Factory {
  public:

    template<class ... T>
    static std::unique_ptr<Base> make(const std::string &s, T &&... args) {
        return data().at(s)(std::forward<T>(args)...);
    }

    template<class T>
    struct Registrar : Base {
        friend T;

        static bool registerT() {
            const auto name = demangle(typeid(T).name());
            Factory::data()[name] = [](Args... args) -> std::unique_ptr<Base> {
                return std::make_unique<T>(std::forward<Args>(args)...);
            };
            return true;
        }
        static bool registered;

      private:
        Registrar() : Base(Key{}) { (void) registered; }
    };

    friend Base;

  private:
    class Key {
        Key() {};
        template<class T> friend
        struct Registrar;
    };
    using FuncType = std::unique_ptr<Base> (*)(Args...);
    Factory() = default;

    static auto &data() {
        static std::unordered_map<std::string, FuncType> s;
        return s;
    }
};

template<class Base, class... Args>
template<class T>
bool Factory<Base, Args...>::Registrar<T>::registered = Factory<Base, Args...>::Registrar<T>::registerT();


#endif //FACTORY_SPLIT_FACTORY_H
