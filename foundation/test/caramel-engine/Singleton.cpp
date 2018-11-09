#include <gtest/gtest.h>

#include "caramel-engine/Singleton.hpp"

using namespace caramel::engine;

namespace /* anonymous */ {

struct DefaultConstructible : Singleton<DefaultConstructible> {
};

struct DefaultConstructibleDisableOnTheFly : Singleton<DefaultConstructibleDisableOnTheFly> {
};

struct NonDefaultConstructible : Singleton<NonDefaultConstructible> {
    NonDefaultConstructible(int) {
    }
};

} // anonymous namespace

namespace caramel::engine {

template <>
struct SingletonTraits<DefaultConstructibleDisableOnTheFly> {
    static constexpr auto ALLOW_ON_THE_FLY_CREATION = false;
};

} // anonymous namespace

namespace /* anonymous */ {

void destroySingletons() {
    DefaultConstructible::destroy();
    DefaultConstructibleDisableOnTheFly::destroy();
    NonDefaultConstructible::destroy();
}

TEST(SingletonTest, InstantiatesDefaultConstructibleOnTheFly) {
    destroySingletons();

    auto& instance1 = DefaultConstructible::instance();
    auto& instance2 = DefaultConstructible::instance();
    EXPECT_EQ(&instance1, &instance2);
}

TEST(SingletonTest, InstantiatesSingletonObjectsOnDemand) {
    destroySingletons();
    
    auto& defaultConstructibleInstance = DefaultConstructible::create();
    EXPECT_EQ(&defaultConstructibleInstance, &DefaultConstructible::instance());

    auto& defaultConstructibleDisableOnTheFlyInstance = DefaultConstructibleDisableOnTheFly::create();
    EXPECT_EQ(&defaultConstructibleDisableOnTheFlyInstance, &DefaultConstructibleDisableOnTheFly::instance());

    auto& nonDefaultConstructibleInstance = NonDefaultConstructible::create(42);
    EXPECT_EQ(&nonDefaultConstructibleInstance, &NonDefaultConstructible::instance());
}

TEST(SingletonDeathTest, AssertsOnInstanceCallsForUninitialisedTypesDisabledOnTheFly) {
    destroySingletons();

    EXPECT_DEATH(DefaultConstructibleDisableOnTheFly::instance(), "\\*theInstance != nullptr");
    EXPECT_DEATH(NonDefaultConstructible::instance(), "\\*theInstance != nullptr");
}

TEST(SingletonDeathTest, AssertsIfCreateCalledForInstantiatedType) {
    destroySingletons();

    DefaultConstructible::instance();
    EXPECT_DEATH(DefaultConstructible::create(), "\\*theInstance == nullptr");

    DefaultConstructibleDisableOnTheFly::create();
    EXPECT_DEATH(DefaultConstructibleDisableOnTheFly::create(), "\\*theInstance == nullptr");

    NonDefaultConstructible::create(42);
    EXPECT_DEATH(NonDefaultConstructible::create(42), "\\*theInstance == nullptr");
}

} // anonymous namespace
