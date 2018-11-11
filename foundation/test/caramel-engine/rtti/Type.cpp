#include <gtest/gtest.h>

#include "caramel-engine/rtti/Type.hpp"
#include "caramel-engine/Singleton.hpp"

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
public:

	RTTI() :
		Type(Field{ })
	{
	}

};

namespace /* anonymous */ {

TEST(RttiTypeTest, FieldsAreAccessible) {
	const auto intType = Type{ "int", {} };
	const auto floatType = Type{ "float", {} };
	const auto stringType = Type{ "std::string", {} };

	const auto otherRtti = Type{
		"Other",
		{
			Field{ stringType, "s", &Other::s }
		}
	};

	const auto mainRtti = Type{
		"Main",
		{
			Field{ intType, "i", &Main::i },
			Field{ floatType, "f", &Main::f },
			Field{ otherRtti, "o", &Main::o }
		}
	};

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

TEST(RttiTypeTest, TypeAccessThroughRTTITemplate) {
	RTTI<Main>
}

} // anonymous namespace
