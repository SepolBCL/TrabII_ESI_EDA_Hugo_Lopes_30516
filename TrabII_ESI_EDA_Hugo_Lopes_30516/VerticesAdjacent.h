/**
 * @file   VericesAdjacent.h
 * @brief  Definições das estruturas e protótipos das funções relacionadas a vértices adjacentes.
 *
 * Este ficheiro contém as definições das estruturas de dados e os protótipos das funções
 * necessárias para manipular vértices adjacentes em um grafo.
 *
 * @date   May 2024
 * @author Hugo Lopes_30516
 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef VRTA
#define VRTA


#include <stdbool.h>

 /**
  * @brief Estrutura para representar as adjacências.
  */
typedef struct Adjacent
{
	int id;
	int peso;
	struct Adjacent* next;
}Adjacent;



Adjacent* NewAdjacent(int id,int peso);
Adjacent* InsertAdj(Adjacent* listaAdj, int idDestino,int peso);
bool DestroyAdjacent(Adjacent* ptAdjacent);
Adjacent* DeleteAdj(Adjacent* listAdj, int codAdj, bool* res);
Adjacent* DeleteAllAdj(Adjacent* listaAdj, bool* res);

#endif /* VRTA */

