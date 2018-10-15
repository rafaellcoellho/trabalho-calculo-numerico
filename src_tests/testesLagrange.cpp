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

TEST(lagrange, intervalo_positivo_de_raizes) {
    double polinomio[] = { 1, -5, -7, 29, 30 };
    int ordem = 4;
    double intervalo_positivo[2];
    double intervalo_negativo[2];
    
    teorema_de_lagrange(polinomio, ordem, intervalo_positivo, intervalo_negativo);
    DOUBLES_EQUAL(0.6743, intervalo_positivo[0], 0.0001);
    DOUBLES_EQUAL(8, intervalo_positivo[1], 0.0001);
}

TEST(lagrange, intervalo_negativo_de_raizes) {
    double polinomio[] = { 1, -5, -7, 29, 30 };
    int ordem = 4;
    double intervalo_positivo[2];
    double intervalo_negativo[2];
    
    teorema_de_lagrange(polinomio, ordem, intervalo_positivo, intervalo_negativo);
    DOUBLES_EQUAL(-6.3852, intervalo_negativo[0], 0.0001);
    DOUBLES_EQUAL(-0.5085, intervalo_negativo[1], 0.0001);
}

TEST(lagrange, limites_corretos_teorema_lagrange) {
    double polinomio[] = { 1, 5, -3, -7, -3 };
    int ordem = 4;
    double intervalo_positivo[2];
    double intervalo_negativo[2];
    
    teorema_de_lagrange(polinomio, ordem, intervalo_positivo, intervalo_negativo);
    DOUBLES_EQUAL(0.457534, intervalo_positivo[0], 0.000001);
    DOUBLES_EQUAL(3.645751, intervalo_positivo[1], 0.000001);
    DOUBLES_EQUAL(-6.000000, intervalo_negativo[0], 0.000001);
    DOUBLES_EQUAL(-0.300000, intervalo_negativo[1], 0.000001);
}

TEST(lagrange, limites_incorretos_teorema_lagrange) {
    double polinomio[] = { 1, 5, 3, 7, 3 };
    int ordem = 4;
    double intervalo_positivo[2];
    double intervalo_negativo[2];
    
    teorema_de_lagrange(polinomio, ordem, intervalo_positivo, intervalo_negativo);
    DOUBLES_EQUAL(0, intervalo_positivo[0], 0.000001);
    DOUBLES_EQUAL(0, intervalo_positivo[1], 0.000001);
}

TEST(lagrange, teorema_de_bolzano_intervalo_com_raiz) {
    double polinomio[] = { 1, 5, -3, -7, -3 };
    int ordem = 4;
    double intervalo[] = {1.0, 2.0};
    
    CHECK_EQUAL(0 ,teorema_de_bolzano(polinomio, ordem, intervalo));
}

TEST(lagrange, teorema_de_bolzano_intervalo_sem_raiz) {
    double polinomio[] = { 1, 5, -3, -7, -3 };
    int ordem = 4;
    double intervalo[] = {2.0, 3.0};
    
    CHECK_EQUAL(1 ,teorema_de_bolzano(polinomio, ordem, intervalo));
}

TEST(lagrange, raiz_aproximada_metodo_bissecao) {
    double polinomio[] = { 1, 5, -3, -7, -3 };
    int ordem = 4;
    double intervalo[2] = {0.0 , 4.0};

    double raiz_aproximada = metodo_da_bissecao(polinomio, ordem, intervalo);
    DOUBLES_EQUAL(1.442585, raiz_aproximada, 0.000001);
}