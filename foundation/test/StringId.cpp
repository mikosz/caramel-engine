#include <gtest/gtest.h>

#include "caramel-engine/StringId.hpp"

using namespace caramel::engine;

namespace /* anonymous */ {

TEST(StringIdTest, StoredStringsCanBeRetrieved) {
    Strings::destroy();

    const auto qwertyId = Strings::instance().add("qwerty");
    const auto azertyId = Strings::instance().add("azerty");

    EXPECT_EQ(qwertyId.string(), "qwerty");
    EXPECT_EQ(azertyId.string(), "azerty");
}

TEST(StringIdTest, StoringSameStringReturnsSameHash) {
    Strings::destroy();

    const auto qwertyId = Strings::instance().add("qwerty");
    const auto qwerty2Id = Strings::instance().add("qwerty");

    EXPECT_EQ(qwertyId, qwerty2Id);
    EXPECT_EQ(qwertyId.string(), "qwerty");
}

TEST(StringIdTest, StringIdIsConstructibleFromString) {
    Strings::destroy();

    const auto fromString = StringId("from string");

    EXPECT_EQ(fromString.string(), "from string");
}

} // anonymous namespace
