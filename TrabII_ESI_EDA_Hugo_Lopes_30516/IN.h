/**
 * @file   IN_OUT.h
 * @author Hugo Lopes_30516
 *
 * @brief Declara��es e defini��es de fun��es para entrada de dados.
 *
 * Este ficheiro cont�m as declara��es e defini��es de fun��es relacionadas � entrada de dados,
 * incluindo a leitura de arquivos para criar e manipular grafos.
 *
 * @date  Maio 2024
 */

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef IN_OUT
#define IN_OUT

 /**
   * @brief Estrutura para representar cria��o de uma lista ligada, atrav�s da leitura de um ficheiro.
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
