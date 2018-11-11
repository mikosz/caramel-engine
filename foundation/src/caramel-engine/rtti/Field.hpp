#ifndef CARAMELENGINE_FOUNDATION_FIELD_HPP__
#define CARAMELENGINE_FOUNDATION_FIELD_HPP__

#include "caramel-engine/StringId.hpp"
#include "caramel-engine/type-info.hpp"

namespace caramel::engine::rtti {

class Type;

class Field {
public:

	Field(const Type& type, StringId name, size_t offset) noexcept :
		type_(type),
		name_(name),
		offset_(offset)
	{
	}

	template <class T, class U>
	Field(const Type& type, StringId name, const U T::*member) :
		Field(type, name, offsetOf(member))
	{
	}

	const Type& type() const noexcept {
		return type_;
	}

	const StringId& name() const noexcept {
		return name_;
	}

	const void* get(const void* object) const noexcept {
		return reinterpret_cast<const char*>(object) + offset_;
	}

	template <class T>
	const T& value(const void* object) const noexcept {
		return *reinterpret_cast<const T*>(get(object));
	}

private:

	const Type& type_;

    const StringId name_;

	const size_t offset_;

};

} // namespace caramel::engine::rtti

#endif /* CARAMELENGINE_FOUNDATION_FIELD_HPP__ */
