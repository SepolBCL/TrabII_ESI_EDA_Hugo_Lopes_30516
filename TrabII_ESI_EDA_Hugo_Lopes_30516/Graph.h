/**
 * @file   Graph.h
 * @brief  Defini��es das estruturas e prot�tipos das fun��es relacionadas a grafos.
 *
 * Este arquivo cont�m as defini��es das estruturas de dados e os prot�tipos das fun��es
 * necess�rias para manipular grafos, incluindo a cria��o, manipula��o e libera��o de mem�ria.
 *
 * @date   May 2024
 * @author Hugo Lopes_30516
 */

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "VerticesAdjacent.h"
#include "Vertices.h"
#include "IN.h"

 /**
  * @brief Estrutura para representar um v�rtice no ficheiro.
  */
typedef struct
{
    int cod;        
    int numAdj;     
} VerticeFile;

/**
 * @brief Estrutura para representar uma adjac�ncia no ficheiro.
 */
typedef struct
{
    int codOrigem;  
    int codDestino; 
    int peso;      
} AdjFile;

/**
 * @brief Estrutura para representar um grafo.
 */
typedef struct Graph
{
    Node* inicioGraph;     
    struct Node* nextVertice; 
    int numeroVertices;     
    int totVertices;        
    int id;                
    bool visitado;         
} Graph;

#define MAX 100
#define MAXDISTANCE -999999

/**
 * @brief Estrutura para armazenar o melhor caminho.
 */
typedef struct {
    int anteriores[MAX];    
    int distance[MAX];      
} Best;

/* Prot�tipos das fun��es */
Graph* CreateGraph(int* totV, bool* res);
Graph* InsertVertGraph(Graph* G, Node* new, bool* res);
Graph* InsertAdjaGraph(Graph* G, int idOrigin, int idDestiny, int peso, bool* res);
Graph* DeleteAdjGraph(Graph* G, int origin, int destiny, bool* res);
Graph* WhereIsVertGraph(Graph* G, int idVertice);
Graph* DeleteVertGraph(Graph* G, int codVertice, bool* res);
bool ExistVertGraph(Graph* inicio, int idVertice);
bool ShowGraph2(Graph* Gr);
Graph* DestroyGraph(Graph* G, bool* res);
Graph* ins_vert_adj(Graph* G, Node2* ini, int* vert, int* adj, bool* res);
int SaveGraph(Graph* G, char* fileName);
Graph* LoadGraphB(char* fileName, bool* res);
Node* FindVerticeId(Graph* g, int cod);
int CountPaths(Graph* g, int src, int dst, int pathCount);
int CountPathsVertices(Graph* g, int src, int dest);
bool DepthFirstSearchRec(Graph* g, int origem, int dest);
Graph* ResetVerticesVisitados(Graph* g);
Best BestPath(Graph* g, int n, int v);
void ShowAllPath(Best b, int n, int v);

#endif /* GRAPH_H */
