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

TEST_GROUP(ep2)
{

	void setup()
	{
	}

	void teardown()
	{
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

/*
	Testes conversão Hexadecimal
*/

/*
	Testes Método de Jordan
*/

TEST(ep2, jordan_com_pivo_zero) {
	double m[3][4] = {
		{2,-2,4,6},
		{2,-2,1,-9},
		{-1,1,-1,2}
	};

	double m_resposta[3][4] = {
		{2,0,0,-14},
		{0,-3,0,-15},
		{0,0,0,0}
	};

	gaussianJordanElimination(m, 3);
	
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			CHECK_EQUAL(m[i][j], m_resposta[i][j]);
		}
	}
}