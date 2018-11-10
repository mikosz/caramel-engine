#include <gtest/gtest.h>

#include "caramel-engine/rtti/Type.hpp"

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

	EXPECT_EQ(mainRtti.field("i").value<int>(&m), 42);
	itd itd itd

	EXPECT_NEAR(mainRtti.field("f").value<float>(&m), 3.14f, 0.0001f);
}

} // anonymous namespace
