#include <CppUTest/TestHarness.h>

extern "C"
{
	#include "../src/ep1.h"
}

TEST_GROUP(ep1)
{
	char *array;

	void setup()
	{
	}

	void teardown()
	{
		free(array);
	}
};

TEST(ep1, convert_zero_to_bin)
{
	array = convert_to_bin(0);
	STRCMP_EQUAL("0.0", array);
}

TEST(ep1, convert_to_bin_without_decimal)
{
	array = convert_to_bin(8);
	STRCMP_EQUAL("1000.0", array);
}

TEST(ep1, convert_to_bin_with_decimal_zero)
{
	array = convert_to_bin(8.0);
	STRCMP_EQUAL("1000.0", array);
}

TEST(ep1, convert_to_bin_with_decimal)
{
	array = convert_to_bin(785.125);
	STRCMP_EQUAL("1100010001.001", array);
}

TEST(ep1, convert_to_bin_decimal_number)
{
	array = convert_to_bin(0.125);
	STRCMP_EQUAL("0.001", array);
}

TEST(ep1, convert_to_bin_periodical)
{
	array = convert_to_bin(0.1);
	STRCMP_EQUAL("0.00011001100110011001", array);
}