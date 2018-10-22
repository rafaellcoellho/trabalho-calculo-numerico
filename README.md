# Trabalho de Calculo Numérico

Trabalho de calculo numérico - IFCE - 2018.2

## Pre-requisitos

Os testes são feitos com o framework [CppUTest](https://github.com/cpputest/cpputest). Você
precisa rodar o script setup-cpputest.sh. Isso vai fazer o download e deixa-lo pronto para ser utilizado.

```
$ cd scripts/
$ ./setup-cpputest.sh
```

## Pastas

- build - Arquivos gerados pela compilação.
- cpputest - O framework de teste.
- scripts - Scripts utilitários.
- src - Código fonte
- src_tests - Testes

## Como utilizar

```
make code_beautifier-> Roda uncrustify no código fonte
make tests          -> Roda os testes
make tests_coverage -> Verifica o cobrimento de testes do projeto
make runnable       -> Compila o projeto
make clean          -> Limpa o projeto
```

## Autores

* **Rafael Coelho** - [rafaellcoellho](https://github.com/rafaellcoellho)
* **Mario Matheus** - [MarioMatheus](https://github.com/MarioMatheus)
