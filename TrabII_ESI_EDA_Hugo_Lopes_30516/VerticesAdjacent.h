/**
 * @file   VericesAdjacent.h
 * @brief  Defini��es das estruturas e prot�tipos das fun��es relacionadas a v�rtices adjacentes.
 *
 * Este ficheiro cont�m as defini��es das estruturas de dados e os prot�tipos das fun��es
 * necess�rias para manipular v�rtices adjacentes em um grafo.
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
  * @brief Estrutura para representar as adjac�ncias.
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

