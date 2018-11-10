#include "Type.hpp"

#include <cassert>
#include <algorithm>

using namespace caramel::engine;
using namespace caramel::engine::rtti;

bool Type::hasField(StringId name) const noexcept {
	return findField(name) != fields_.end();
}

const Field& Type::field(StringId name) const noexcept {
	const auto fieldIt = findField(name);

	assert(fieldIt != fields_.end());

	return *fieldIt;
}

auto Type::findField(StringId name) const noexcept -> Fields::const_iterator {
	return std::find_if(fields_.begin(), fields_.end(), [name](const auto& field) {
			return field.name() == name;
		}
	);
}
