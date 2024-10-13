/**
 * @file   Vertices.h
 * @brief  Definições das estruturas e protótipos das funções relacionadas a vértices.
 *
 * Este arquivo contém as definições das estruturas de dados e os protótipos das funções
 * necessárias para manipular vértices em um grafo.
 *
 * @date   May 2024
 * @author Hugo Lopes_30516
 */

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef VRT
#define VRT

#include <stdbool.h>
#include"VerticesAdjacent.h"

 /**
  * @brief Estrutura para representar os vértices.
  */
typedef struct Node
{
    int id;
    bool visitado;
    struct Adjacent* nextAdjacent;
    struct Node* nextVertice;
} Node;


Node* CreateVertice(int id, bool* res);
Node* InsertVertice(Node* vertices, Node* novo, bool* res);
Node* DeleteVertice(Node* vertices, int codVertice, bool* res);
Node* WhereIsVertice(Node* inicio, int id);
Node* DeleteAllAdjVert(Node* vertices, int codAdj, bool* res);
bool ExistVertice(Node* inicio, int id);
bool ShowGraph(Node* graph);
bool DestroiVertice(Node* ptNode);

#endif /* VRT */
