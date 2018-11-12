#ifndef CARAMELENGINE_FOUNDATION_STRINGID_HPP__
#define CARAMELENGINE_FOUNDATION_STRINGID_HPP__

#include <string>
#include <iosfwd>
#include <unordered_map>

#include "Singleton.hpp"
#include "functional.hpp"

namespace caramel::engine {

class StringId {
public:

    StringId() noexcept = default;

    StringId(std::string s);

    StringId(const char* cs) :
        StringId(std::string(cs))
    {
    }

    const std::string& string() const noexcept;

private:

    using Hash = std::size_t;

    static const auto INVALID_HASH = static_cast<Hash>(-1);

    Hash hash_ = INVALID_HASH;

    StringId(Hash hash) :
        hash_(hash)
    {
    }

    friend bool operator==(StringId lhs, StringId rhs) {
        return lhs.hash_ == rhs.hash_;
    }

    friend class Strings;

    friend struct std::hash<StringId>;

};

inline std::ostream& operator<<(std::ostream& os, StringId stringId) {
    return os << stringId.string();
}

class Strings : public Singleton<Strings> {
public:

    StringId add(std::string s);

private:

    using Registry = std::unordered_map<StringId::Hash, std::string, Identity>;

    Registry registry_;

	Strings() = default;

    const std::string& get(StringId::Hash hash) const {
        const auto it = registry_.find(hash);
        assert(it != registry_.end());
        return it->second;
    }

	friend class Singleton<Strings>;

    friend class StringId;

};

inline StringId::StringId(std::string s) :
    StringId(Strings::instance().add(std::move(s)))
{
}

inline const std::string& StringId::string() const noexcept {
    assert(hash_ != INVALID_HASH);
    return Strings::instance().get(hash_);
}

} // namespace caramel::engine

namespace std {

template <>
struct hash<caramel::engine::StringId> {

    size_t operator()(caramel::engine::StringId stringId) const noexcept {
        return stringId.hash_;
    }

};

} // namespace std

#endif /* CARAMELENGINE_FOUNDATION_STRINGID_HPP__ */
