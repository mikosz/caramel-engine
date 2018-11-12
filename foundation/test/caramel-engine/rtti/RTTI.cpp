#include <gtest/gtest.h>

#include "caramel-engine/rtti/Type.hpp"
#include "caramel-engine/rtti/RTTI.hpp"
#include "caramel-engine/Singleton.hpp"

using namespace caramel;
using namespace caramel::engine;
using namespace caramel::engine::rtti;

namespace /* anonymous */ {

struct Other {
	std::string s;
};

struct Main {
	int i;
	float f;
	Other o;
};

} // anonymous namespace

template <>
class RTTI<Other> : public Singleton<RTTI<Other>>, public Type {
private:

	RTTI() :
		Type("Other", {
			Field{ RTTI<std::string>::instance(), "s", &Other::s }
			})
	{
	}

	friend class Singleton<RTTI<Other>>;

};

template <>
class RTTI<Main> : public Singleton<RTTI<Main>>, public Type {
private:

	RTTI() :
		Type("Main", {
			Field{ RTTI<int>::instance(), "i", &Main::i },
			Field{ RTTI<float>::instance(), "f", &Main::f },
			Field{ RTTI<Other>::instance(), "o", &Main::o }
			})
	{
	}

	friend class Singleton<RTTI<Main>>;

};

namespace /* anonymous */ {

TEST(RttiRTTITest, TypeAccessThroughRTTITemplate) {
	const auto& mainRtti = RTTI<Main>::instance();
	const auto& otherRtti = RTTI<Other>::instance();

	const auto m = Main{ 42, 3.14f, { "Hey there!" }};

	EXPECT_TRUE(mainRtti.hasField("i"));
	EXPECT_TRUE(mainRtti.hasField("f"));
	EXPECT_TRUE(mainRtti.hasField("o"));
	EXPECT_TRUE(otherRtti.hasField("s"));
	EXPECT_FALSE(mainRtti.hasField("not there"));

	const auto& iField = mainRtti.field("i");
	EXPECT_EQ(iField.type().name(), "int");
	EXPECT_EQ(iField.name(), "i");
	EXPECT_EQ(iField.value<int>(&m), 42);

	const auto& fField = mainRtti.field("f");
	EXPECT_EQ(fField.type().name(), "float");
	EXPECT_EQ(fField.name(), "f");
	EXPECT_NEAR(mainRtti.field("f").value<float>(&m), 3.14f, 0.0001f);

	const auto& oField = mainRtti.field("o");
	const auto& osField = oField.type().field("s");
	EXPECT_EQ(osField.type().name(), "std::string");
	EXPECT_EQ(osField.name(), "s");
	EXPECT_EQ(osField.value<std::string>(oField.get(&m)), "Hey there!");
}

TEST(RttiRTTITest, TypeAccessThroughPolymorphicMethod) {
	auto rttiObject = poly::Poly<RTTIObject>(Main{ 42, 3.14f, { "Hey there!" }});

	const auto& mainRtti = rttiObject.invoke(RTTI_METHOD_LABEL);
	const auto& otherRtti = mainRtti.field("o").type();

	EXPECT_TRUE(mainRtti.hasField("i"));
	EXPECT_TRUE(mainRtti.hasField("f"));
	EXPECT_TRUE(mainRtti.hasField("o"));
	EXPECT_TRUE(otherRtti.hasField("s"));
	EXPECT_FALSE(mainRtti.hasField("not there"));

	const auto& iField = mainRtti.field("i");
	EXPECT_EQ(iField.type().name(), "int");
	EXPECT_EQ(iField.name(), "i");
	EXPECT_EQ(iField.value<int>(rttiObject.unsafeGet<void>()), 42);

	const auto& fField = mainRtti.field("f");
	EXPECT_EQ(fField.type().name(), "float");
	EXPECT_EQ(fField.name(), "f");
	EXPECT_NEAR(mainRtti.field("f").value<float>(rttiObject.unsafeGet<void>()), 3.14f, 0.0001f);

	const auto& oField = mainRtti.field("o");
	const auto& osField = oField.type().field("s");
	EXPECT_EQ(osField.type().name(), "std::string");
	EXPECT_EQ(osField.name(), "s");
	EXPECT_EQ(osField.value<std::string>(oField.get(rttiObject.unsafeGet<void>())), "Hey there!");
}

} // anonymous namespace
