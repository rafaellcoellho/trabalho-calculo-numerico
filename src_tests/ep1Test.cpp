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

/*
	Testes conversão binária
*/

TEST(ep1, convert_zero_to_bin)
{
	array = convert(0, 2);
	STRCMP_EQUAL("0.0", array);
}

TEST(ep1, convert_to_bin_without_decimal)
{
	array = convert(8, 2);
	STRCMP_EQUAL("1000.0", array);
}

TEST(ep1, convert_to_bin_with_decimal_zero)
{
	array = convert(8.0, 2);
	STRCMP_EQUAL("1000.0", array);
}

TEST(ep1, convert_to_bin_with_decimal)
{
	array = convert(785.125, 2);
	STRCMP_EQUAL("1100010001.001", array);
}

TEST(ep1, convert_to_bin_decimal_number)
{
	array = convert(0.125, 2);
	STRCMP_EQUAL("0.001", array);
}

TEST(ep1, convert_to_bin_periodical)
{
	array = convert(0.1, 2);
	STRCMP_EQUAL("0.00011001100110011001", array);
}

/*
	Testes conversão Octal
*/

TEST(ep1, convert_zero_to_octal)
{
	array = convert(0, 8);
	STRCMP_EQUAL("0.0", array);
}

TEST(ep1, convert_to_octal_without_decimal)
{
	array = convert(10, 8);
	STRCMP_EQUAL("12.0", array);
}

TEST(ep1, convert_to_octal_with_decimal_zero)
{
	array = convert(219.0, 8);
	STRCMP_EQUAL("333.0", array);
}

TEST(ep1, convert_to_octal_with_decimal)
{
	array = convert(219.59375, 8);
	STRCMP_EQUAL("333.46", array);
}

TEST(ep1, convert_to_octal_decimal_number)
{
	array = convert(0.359375, 8);
	STRCMP_EQUAL("0.27", array);
}