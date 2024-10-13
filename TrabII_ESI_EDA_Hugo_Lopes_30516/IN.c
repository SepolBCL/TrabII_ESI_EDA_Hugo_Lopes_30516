/**
 * @file   IN_OUT.c
 * @author Hugo Lopes_30516
 *
 * @brief Implementa��o das fun��es de entrada para manipula��o de grafos.
 *
 * Este ficheiro cont�m a implementa��o das fun��es respons�veis pela leitura de ficheiros
 * e manipula��o de estruturas de dados para representar grafos.
 *
 * @date   Maio 2024
 */



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <stdbool.h>
#include"IN.h"
#include"Vertices.h"
#include"VerticesAdjacent.h"
#include"Graph.h"

#pragma region Cria um novo peso de adjac�ncia especificado.
 /**
 * Cria um novo n� com o peso especificado.
 *
 * @param peso2 O peso do n� a ser criado.
 * @return Um apontador para o novo n� criado, ou NULL se a aloca��o de mem�ria falhar.
 */
Node2* novoNo(int peso2)
{
    // Aloca mem�ria para o novo n�
    Node2* aux = (Node2*)malloc(sizeof(Node2));

    // Verifica se a aloca��o de mem�ria foi bem-sucedida
    if (aux == NULL) return NULL;

    // Inicializa o campo 'peso2' do novo n� com o valor fornecido
    aux->peso2 = peso2;

    // Inicializa o ponteiro 'next' do novo n� como NULL
    aux->next = NULL;

    // Retorna o apontador para o novo n�
    return aux;
}
#pragma endregion


#pragma region Insere um n� no final da lista.
/**
 * Insere um n� no final da lista.
 *
 * @param head O apontador para o in�cio da lista.
 * @param peso2 O apontador para a adja a ser inserido.
 * @return O apontador para o in�cio da lista ap�s a inser��o do novo n�.
 */
Node2* InsereFim(Node2* head, Node2* peso2)
{
    // Verifica se o n� a ser inserido � NULL
    if (peso2 == NULL) return head;

    // Se a lista estiver vazia, o n� a ser inserido ser� o primeiro da lista
    if (head == NULL) return peso2;
    else 
    {
        // Percorre a lista at� o �ltimo n�
        Node2* aux = head;
        while (aux->next != NULL)
            aux = aux->next;

        // Insere o novo n� no final da lista
        aux->next = peso2;
    }

    // Retorna o apontador para o in�cio da lista
    return head;
}
#pragma endregion


#pragma region L� uma matriz de um ficheiro para criar uma lista ligada.
 
/**
 * L� uma matriz de um ficheiro onde as linhas representam v�rtices e as colunas representam adjac�ncias,
 * e cria uma lista ligada de n�s representando os elementos da matriz.
 *
 * @param ficheiro O nome do ficheiro a ser lido.
 * @param totV Apontador para a vari�vel que armazenar� o n�mero total de v�rtices (linhas).
 * @param totA Apontador para a vari�vel que armazenar� o n�mero total de adjac�ncias (colunas).
 * @param res Apontador para uma vari�vel bool onde ser� armazenado o resultado da opera��o.
 *            Ser� definido como verdadeiro se a leitura for bem-sucedida, ou falso caso contr�rio.
 * @return Apontador para o in�cio da lista ligada de n�s, ou NULL se a leitura falhar.
 */
Node2* readFile(const char* ficheiro, int* totV, int* totA, bool* res)
{
    // Inicializa a lista ligada como vazia
    Node2* head = NULL;

    // Abre o ficheiro para leitura
    FILE* fp = fopen(ficheiro, "r");
    if (fp == NULL)
    {
        // Se a abertura do ficheiro falhar, define o resultado como falso e retorna NULL
        if (res != NULL)
            *res = false;
        return NULL;
    }
    // Se a abertura do ficheiro for bem-sucedida, define o resultado como verdadeiro
    if (res != NULL)
        *res = true;

    int peso2;
    char delimitador; // Vari�vel para o delimitador
    *totV = 1; // Inicializa o n�mero de v�rtices
    *totA = 0; // Inicializa o n�mero de adjac�ncias

    // Loop para ler os n�meros do ficheiro e criar n�s para cada elemento da matriz
    while (fscanf(fp, "%d%c", &peso2, &delimitador) != EOF)
    {
        // Cria um novo n� com o valor lido
        Node2* novo = novoNo(peso2);
        if (novo == NULL)
            return NULL;

        // Insere o novo n� no final da lista
        head = InsereFim(head, novo);
        (*totA)++;

        // Verifica se chegou ao final da linha 
        if (delimitador == '\n')
        {
            // Incrementa o n�mero de v�rtices
            (*totV)++;
            (*totA) = 0; // Reinicia o n�mero de adjac�ncias para a pr�xima linha
        }
    }

    // Fecha o ficheiro ap�s a leitura
    fclose(fp);

    // Retorna o apontador para o in�cio da lista ligada de n�s
    return head;
}
#pragma endregion


