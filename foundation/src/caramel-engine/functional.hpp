#ifndef CARAMELENGINE_FOUNDATION_FUNCTIONAL_HPP__
#define CARAMELENGINE_FOUNDATION_FUNCTIONAL_HPP__

namespace caramel::engine {

struct Identity {
    template <class T>
    T operator()(T v) const {
        return std::move(v);
    }
};

} // namespace caramel::engine

#endif /* CARAMELENGINE_FOUNDATION_FUNCTIONAL_HPP__ */
