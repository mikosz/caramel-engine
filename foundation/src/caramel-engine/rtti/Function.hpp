#ifndef CARAMELENGINE_FOUNDATION_RTTI_FUNCTION_HPP__
#define CARAMELENGINE_FOUNDATION_RTTI_FUNCTION_HPP__

#include <vector>

#include "caramel-engine/StringId.hpp"
#include "Type.hpp"

namespace caramel::engine::rtti {

class Function {
public:

	Function(StringId name) :
		name_(name)
	{
	}

private:

	using Arguments = std::vector<Type>;

	const StringId name_;

};

} // namespace caramel::engine::rtti

#endif /* CARAMELENGINE_FOUNDATION_RTTI_FUNCTION_HPP__ */
