#ifndef CARAMELENGINE_FOUNDATION_TYPEINFO_HPP__
#define CARAMELENGINE_FOUNDATION_TYPEINFO_HPP__

namespace caramel::engine {

template<class T, class U>
constexpr size_t offsetOf(U T::*member) {
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

} // namespace caramel::engine

#endif /* CARAMELENGINE_FOUNDATION_TYPEINFO_HPP__ */
