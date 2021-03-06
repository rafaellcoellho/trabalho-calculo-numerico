#include <CppUTest/TestHarness.h>

extern "C"
{
	#include "../src/ep1.h"
}

TEST_GROUP(jordan)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

/*
	Testes Método de Jordan
*/

TEST(jordan, jordan_com_nenhum_pivo_zero) {
	double m_valores[3][4] = {
		{ 1 , 5 ,-2 ,11 },
		{-2 , 4 , 1 , 3 },
		{ 3 ,-1 , 4 ,11 }
	};

	double **m = aloca_matriz(3,4);
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

	metodo_de_jordan(m, 3, x);

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

TEST(jordan, jordan_com_pivo_zero) {
	double m_valores[3][4] = {
		{ 2 ,-2 , 4 , 6 },
		{ 2 ,-2 , 1 ,-9 },
		{-1 , 1 ,-1 , 2 }
	};

	double **m = aloca_matriz(3,4);
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

	metodo_de_jordan(m, 3, x);

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

TEST(jordan, checa_array_de_ordem_sem_troca_de_coluna) {
	double m_valores[3][4] = {
		{ 1 , 5 ,-2 ,11 },
		{-2 , 4 , 1 , 3 },
		{ 3 ,-1 , 4 ,11 }
	};

	double **m = aloca_matriz(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[3];

	metodo_de_jordan(m, 3, x);

	CHECK_EQUAL(x[0], 0);
	CHECK_EQUAL(x[1], 1);
	CHECK_EQUAL(x[2], 2);
	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(jordan, checa_array_de_ordem_com_troca_de_coluna) {
	double m_valores[3][4] = {
		{ 2 ,-2 , 4 , 6 },
		{ 2 ,-2 , 1 ,-9 },
		{-1 , 1 ,-1 , 2 }
	};

	double **m = aloca_matriz(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[3];

	metodo_de_jordan(m, 3, x);

	CHECK_EQUAL(x[0], 0);
	CHECK_EQUAL(x[1], 2);
	CHECK_EQUAL(x[2], 1);
	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(jordan, checa_solucao) {
	double m_valores[3][4] = {
		{ 1 , 5 ,-2 ,11 },
		{-2 , 4 , 1 , 3 },
		{ 3 ,-1 , 4 ,11 }
	};

	double **m = aloca_matriz(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[3];
	double result[3];

	metodo_de_jordan(m, 3, x);
	soluciona_matriz_diagonal(m, 3, result);

	DOUBLES_EQUAL(3, result[0], 0.001);
	DOUBLES_EQUAL(2, result[1], 0.001);
	DOUBLES_EQUAL(1, result[2], 0.001);
	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(jordan, checa_solucao_indexada_por_array_de_ordem) {
	double m_valores[3][4] = {
		{ 2 ,-2 , 4 , 6 },
		{ 2 ,-2 , 1 ,-9 },
		{-1 , 1 ,-1 , 2 }
	};

	double **m = aloca_matriz(3,4);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[3];
	double result[3];

	metodo_de_jordan(m, 3, x);
	soluciona_matriz_diagonal(m, 3, result);

	DOUBLES_EQUAL(-7, result[x[0]], 0.001);
	DOUBLES_EQUAL(0, result[x[1]], 0.001);
	DOUBLES_EQUAL(5, result[x[2]], 0.001);
	
	for (int i = 0; i < 3; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(jordan, checa_sistema_compativel_determinado) {
	double m_valores[2][3] = {
		{ 2 , 3 , 18 },
		{ 3 , 4 , 25 }
	};

	double **m = aloca_matriz(2,3);
	for(int i = 0; i<2; i++){
		for(int j = 0; j<3; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[2];
	double result[2];

	metodo_de_jordan(m, 2, x);
	int tipo = soluciona_matriz_diagonal(m, 2, result);
	
	CHECK_EQUAL(0, tipo);	
	
	for (int i = 0; i < 2; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(jordan, checa_sistema_compativel_indeterminado) {
	double m_valores[2][3] = {
		{ 4 , 2 , 100 },
		{ 8 , 4 , 200 }
	};

	double **m = aloca_matriz(2,3);
	for(int i = 0; i<2; i++){
		for(int j = 0; j<3; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[2];
	double result[2];

	metodo_de_jordan(m, 2, x);
	int tipo = soluciona_matriz_diagonal(m, 2, result);
	
	CHECK_EQUAL(1, tipo);	
	
	for (int i = 0; i < 2; i++) {
		free(m[i]);
	}
	free(m);
}

TEST(jordan, checa_sistema_incompativel) {
	double m_valores[2][3] = {
		{ 3 , 9 , 12 },
		{ 3 , 9 , 15 }
	};

	double **m = aloca_matriz(2,3);
	for(int i = 0; i<2; i++){
		for(int j = 0; j<3; j++) {
			m[i][j] = m_valores[i][j];
		}
	}

	int x[2];
	double result[2];

	metodo_de_jordan(m, 2, x);
	int tipo = soluciona_matriz_diagonal(m, 2, result);
	
	CHECK_EQUAL(2, tipo);	
	
	for (int i = 0; i < 2; i++) {
		free(m[i]);
	}
	free(m);
}