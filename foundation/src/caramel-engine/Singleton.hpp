#ifndef CARAMELENGINE_SINGLETON_HPP__
#define CARAMELENGINE_SINGLETON_HPP__

#include <type_traits>
#include <cassert>
#include <cstdlib>

namespace caramel::engine {

template <class T>
struct SingletonTraits {
    static constexpr auto ALLOW_ON_THE_FLY_CREATION = std::is_default_constructible_v<T>;
};

template <class T>
class Singleton {
public:

    template <class... Args>
    static T& create(Args&&... args) {
        auto** theInstance = instanceHolder();
        assert(*theInstance == nullptr);
        *theInstance = new T(std::forward<Args>(args)...);
        std::atexit(&Singleton::destroy);
        return **theInstance;
    }

    static void destroy() {
        auto** theInstance = instanceHolder();
        delete *theInstance;
        *theInstance = nullptr;
    }

    static T& instance() {
        auto** theInstance = instanceHolder();

        if constexpr (SingletonTraits<T>::ALLOW_ON_THE_FLY_CREATION) {
            if (*theInstance == nullptr)
            {
                *theInstance = new T;
                std::atexit(&Singleton::destroy);
            }
        } else {
            assert(*theInstance != nullptr);
        }

        return **theInstance;
    }

protected:

    Singleton() = default;

private:

    static T** instanceHolder() {
        static T* theInstance = nullptr;
        return &theInstance;
    }

};

} // namespace caramel::engine

#endif /* CARAMELENGINE_SINGLETON_HPP__ */
