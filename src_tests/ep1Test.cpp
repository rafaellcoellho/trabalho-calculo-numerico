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

TEST(ep2, jordan_com_diagonal_nao_nula) {
	double m_valores[3][4] = {
		{ 1 , 5 ,-2 ,11 },
		{-2 , 4 , 1 , 3 },
		{ 3 ,-1 , 4 ,11 }
	};

	double **m = allocateMatrix(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	double m_resposta[3][4] = {
		{ 1 , 0 , 0 , 3 },
		{ 0 ,14 , 0 , 28 },
		{ 0 , 0 ,6.571 , 6.571 }
	};

	int x[3];

	gaussianJordanElimination(m, 3, x);

	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			DOUBLES_EQUAL(m[i][j], m_resposta[i][j], 0.001);
		}
	}

	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(ep2, jordan_com_pivo_zero) {
	double m_valores[3][4] = {
		{ 2 ,-2 , 4 , 6 },
		{ 2 ,-2 , 1 ,-9 },
		{-1 , 1 ,-1 , 2 }
	};

	double **m = allocateMatrix(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	double m_resposta[3][4] = {
		{ 2 , 0 , 0 ,-14 },
		{ 0 ,-3 , 0 ,-15 },
		{ 0 , 0 , 0 ,  0 }
	};

	int x[3];

	gaussianJordanElimination(m, 3, x);

	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			DOUBLES_EQUAL(m[i][j], m_resposta[i][j], 0.001);
		}
	}

	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(ep2, jordan_disposicao_normal_variaveis) {
	double m_valores[3][4] = {
		{ 1 , 5 ,-2 ,11 },
		{-2 , 4 , 1 , 3 },
		{ 3 ,-1 , 4 ,11 }
	};

	double **m = allocateMatrix(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[3];

	gaussianJordanElimination(m, 3, x);

	CHECK_EQUAL(x[0], 1);
	CHECK_EQUAL(x[1], 2);
	CHECK_EQUAL(x[2], 3);
	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(ep2, jordan_disposica0_alterada_variaveis) {
	double m_valores[3][4] = {
		{ 2 ,-2 , 4 , 6 },
		{ 2 ,-2 , 1 ,-9 },
		{-1 , 1 ,-1 , 2 }
	};

	double **m = allocateMatrix(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[3];

	gaussianJordanElimination(m, 3, x);

	CHECK_EQUAL(x[0], 1);
	CHECK_EQUAL(x[1], 3);
	CHECK_EQUAL(x[2], 2);
	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}