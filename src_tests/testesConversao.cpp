#include <CppUTest/TestHarness.h>

extern "C"
{
	#include "../src/ep1.h"
}

TEST_GROUP(conversao)
{
	char *string;

	void setup()
	{
	}

	void teardown()
	{
		free(string);
	}
};

/*
	Testes conversão binária
*/

TEST(conversao, zero_para_binario)
{
	string = convert(0, 2);
	STRCMP_EQUAL("0.0", string);
}

TEST(conversao, numero_inteiro_para_binario)
{
	string = convert(8, 2);
	STRCMP_EQUAL("1000.0", string);
}

TEST(conversao, numero_fracionario_zero_para_binario)
{
	string = convert(8.0, 2);
	STRCMP_EQUAL("1000.0", string);
}

TEST(conversao, numero_com_parte_fracionaria_para_binario)
{
	string = convert(785.125, 2);
	STRCMP_EQUAL("1100010001.001", string);
}

TEST(conversao, numero_fracionario_para_binario)
{
	string = convert(0.125, 2);
	STRCMP_EQUAL("0.001", string);
}

TEST(conversao, dizima_periodica_para_binario)
{
	string = convert(0.1, 2);
	STRCMP_EQUAL("0.00011001100110011001", string);
}

/*
	Testes conversão Octal
*/

TEST(conversao, zero_para_octal)
{
	string = convert(0, 8);
	STRCMP_EQUAL("0.0", string);
}

TEST(conversao, numero_inteiro_para_octal)
{
	string = convert(10, 8);
	STRCMP_EQUAL("12.0", string);
}

TEST(conversao, numero_fracionario_zero_para_octal)
{
	string = convert(219.0, 8);
	STRCMP_EQUAL("333.0", string);
}

TEST(conversao, numero_com_parte_fracionaria_para_octal)
{
	string = convert(219.59375, 8);
	STRCMP_EQUAL("333.46", string);
}

TEST(conversao, numero_fracionario_para_octal)
{
	string = convert(0.359375, 8);
	STRCMP_EQUAL("0.27", string);
}

/*
	Testes conversão Hexadecimal
*/

