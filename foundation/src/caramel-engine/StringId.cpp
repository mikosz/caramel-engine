#include "StringId.hpp"

#include <cassert>

using namespace caramel::engine;

StringId Strings::add(std::string s) {
    const auto hash = std::hash<std::string>()(s);
    const auto it = registry_.find(hash);

    assert(it == registry_.end() || it->second == s);

    if (it == registry_.end()) {
        registry_.emplace_hint(it, hash, std::move(s));
    }

    return hash;
}
