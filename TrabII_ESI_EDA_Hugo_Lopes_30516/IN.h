/**
 * @file   IN_OUT.h
 * @author Hugo Lopes_30516
 *
 * @brief Declarações e definições de funções para entrada de dados.
 *
 * Este ficheiro contém as declarações e definições de funções relacionadas à entrada de dados,
 * incluindo a leitura de arquivos para criar e manipular grafos.
 *
 * @date  Maio 2024
 */

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef IN_OUT
#define IN_OUT

 /**
   * @brief Estrutura para representar criação de uma lista ligada, através da leitura de um ficheiro.
   */
typedef struct Node2 
{
    int peso2;
    int id;
    struct Node2* next;
} Node2;

Node2* novoNo(int peso2);
Node2* InsereFim(Node2* head, Node2* peso2);
Node2* readFile(const char* ficheiro, int* totV, int* totA, bool* res);

#endif /* IN */
