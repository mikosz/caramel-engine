#ifndef CARAMELENGINE_FOUNDATION_RTTI_HPP__
#define CARAMELENGINE_FOUNDATION_RTTI_HPP__

#include <type_traits>
#include <string>

#include <caramel-poly/Poly.hpp>

#include "caramel-engine/Singleton.hpp"
#include "Type.hpp"

namespace caramel::engine::rtti {

template <class T, class = void>
class RTTI;

template <class T>
class RTTI<T, std::enable_if_t<std::is_arithmetic_v<T>>> :
	public Singleton<RTTI<T>>,
	public Type
{
private:

	RTTI() :
		Type(typeid(std::decay_t<T>).name(), {})
	{
	}

	friend class Singleton<RTTI<T>>;

};

template <>
class RTTI<std::string> :
	public Singleton<RTTI<std::string>>,
	public Type
{
private:

	RTTI() :
		Type("std::string", {})
	{
	}

	friend class Singleton<RTTI<std::string>>;

};

constexpr auto RTTI_METHOD_LABEL = POLY_FUNCTION_LABEL("rtti");

struct RTTIObject : decltype(poly::requires(
	RTTI_METHOD_LABEL = poly::method<const Type& () const>
	))
{
};

} // namespace caramel::engine::rtti

template <class T>
constexpr auto caramel::poly::defaultConceptMap<caramel::engine::rtti::RTTIObject, T> = caramel::poly::makeConceptMap(
	caramel::engine::rtti::RTTI_METHOD_LABEL =
		[](const auto&) -> decltype(auto) { return caramel::engine::rtti::RTTI<T>::instance(); }
	);

#endif /* CARAMELENGINE_FOUNDATION_RTTI_HPP__ */
