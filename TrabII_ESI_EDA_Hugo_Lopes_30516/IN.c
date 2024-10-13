/**
 * @file   IN_OUT.c
 * @author Hugo Lopes_30516
 *
 * @brief Implementação das funções de entrada para manipulação de grafos.
 *
 * Este ficheiro contém a implementação das funções responsáveis pela leitura de ficheiros
 * e manipulação de estruturas de dados para representar grafos.
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

#pragma region Cria um novo peso de adjacência especificado.
 /**
 * Cria um novo nó com o peso especificado.
 *
 * @param peso2 O peso do nó a ser criado.
 * @return Um apontador para o novo nó criado, ou NULL se a alocação de memória falhar.
 */
Node2* novoNo(int peso2)
{
    // Aloca memória para o novo nó
    Node2* aux = (Node2*)malloc(sizeof(Node2));

    // Verifica se a alocação de memória foi bem-sucedida
    if (aux == NULL) return NULL;

    // Inicializa o campo 'peso2' do novo nó com o valor fornecido
    aux->peso2 = peso2;

    // Inicializa o ponteiro 'next' do novo nó como NULL
    aux->next = NULL;

    // Retorna o apontador para o novo nó
    return aux;
}
#pragma endregion


#pragma region Insere um nó no final da lista.
/**
 * Insere um nó no final da lista.
 *
 * @param head O apontador para o início da lista.
 * @param peso2 O apontador para a adja a ser inserido.
 * @return O apontador para o início da lista após a inserção do novo nó.
 */
Node2* InsereFim(Node2* head, Node2* peso2)
{
    // Verifica se o nó a ser inserido é NULL
    if (peso2 == NULL) return head;

    // Se a lista estiver vazia, o nó a ser inserido será o primeiro da lista
    if (head == NULL) return peso2;
    else 
    {
        // Percorre a lista até o último nó
        Node2* aux = head;
        while (aux->next != NULL)
            aux = aux->next;

        // Insere o novo nó no final da lista
        aux->next = peso2;
    }

    // Retorna o apontador para o início da lista
    return head;
}
#pragma endregion


#pragma region Lê uma matriz de um ficheiro para criar uma lista ligada.
 
/**
 * Lê uma matriz de um ficheiro onde as linhas representam vértices e as colunas representam adjacências,
 * e cria uma lista ligada de nós representando os elementos da matriz.
 *
 * @param ficheiro O nome do ficheiro a ser lido.
 * @param totV Apontador para a variável que armazenará o número total de vértices (linhas).
 * @param totA Apontador para a variável que armazenará o número total de adjacências (colunas).
 * @param res Apontador para uma variável bool onde será armazenado o resultado da operação.
 *            Será definido como verdadeiro se a leitura for bem-sucedida, ou falso caso contrário.
 * @return Apontador para o início da lista ligada de nós, ou NULL se a leitura falhar.
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
    char delimitador; // Variável para o delimitador
    *totV = 1; // Inicializa o número de vértices
    *totA = 0; // Inicializa o número de adjacências

    // Loop para ler os números do ficheiro e criar nós para cada elemento da matriz
    while (fscanf(fp, "%d%c", &peso2, &delimitador) != EOF)
    {
        // Cria um novo nó com o valor lido
        Node2* novo = novoNo(peso2);
        if (novo == NULL)
            return NULL;

        // Insere o novo nó no final da lista
        head = InsereFim(head, novo);
        (*totA)++;

        // Verifica se chegou ao final da linha 
        if (delimitador == '\n')
        {
            // Incrementa o número de vértices
            (*totV)++;
            (*totA) = 0; // Reinicia o número de adjacências para a próxima linha
        }
    }

    // Fecha o ficheiro após a leitura
    fclose(fp);

    // Retorna o apontador para o início da lista ligada de nós
    return head;
}
#pragma endregion


