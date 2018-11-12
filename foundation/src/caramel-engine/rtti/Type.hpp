#ifndef CARAMELENGINE_FOUNDATION_TYPE_HPP__
#define CARAMELENGINE_FOUNDATION_TYPE_HPP__

#include <vector>
#include <initializer_list>

#include "caramel-engine/StringId.hpp"
#include "Field.hpp"

namespace caramel::engine::rtti {

class Type {
public:

	Type(StringId name, std::initializer_list<Field> fields) :
		name_(std::move(name)),
		fields_(std::move(fields))
	{
	}

	bool hasField(StringId name) const noexcept;

	const Field& field(StringId name) const noexcept;

	StringId name() const noexcept {
		return name_;
	}

private:

    using Fields = std::vector<Field>;

	const StringId name_;

	const Fields fields_;

	Fields::const_iterator findField(StringId name) const noexcept;

};

} // namespace caramel::engine::rtti

#endif /* CARAMELENGINE_FOUNDATION_TYPE_HPP__ */
