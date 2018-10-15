#include <CppUTest/TestHarness.h>

extern "C"
{
	#include "../src/ep1.h"
}

TEST_GROUP(lagrange)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

/*
    Testes do teorema de lagrange e do metodo da bissecao
*/
TEST(lagrange, limites_corretos_teorema_lagrange) {
    double polinomio[] = { 1, 5, -3, -7, -3 };
    double ordem = 4;
    double intervalo_positivo[2];
    double intervalo_negativo[2];
    
    aplicar_teorema_de_langrange(polinomio, ordem, intervalo_positivo, intervalo_negativo);
    DOUBLES_EQUAL(0.457534, intervalo_positivo[0], 0.000001);
    DOUBLES_EQUAL(3.645751, intervalo_positivo[1], 0.000001);
    DOUBLES_EQUAL(-6.000000, intervalo_negativo[0], 0.000001);
    DOUBLES_EQUAL(-0.300000, intervalo_negativo[1], 0.000001);
}


TEST(lagrange, raiz_aproximada_metodo_bissecao) {
    double polinomio[] = { 1, 5, -3, -7, -3 };
    double ordem = 4;
    double intervalo[2] = {0.0 , 4.0};

    double raiz_aproximada = aplicar_metodo_da_bissecao(polinomio, ordem, intervalo);
    DOUBLES_EQUAL(1.442585, raiz_aproximada, 0.000001);
}
