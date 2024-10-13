/**
 * @file   VerticesAdjacent.c
 * @author Hugo Lopes_30516
 *
 * @brief Definição das funções relacionadas a vértices adjacentes.
 *
 * Este ficheiro contém a implementação das funções responsáveis por operações
 * relacionadas a vértices adjacentes em grafos.
 *
 * @date   May 2024
 */

#include<malloc.h>
#include <stdbool.h>
#include"VerticesAdjacent.h"


#pragma region Cria um novo nó de adjacência com o ID especificado.
 /**
 * @brief Cria um novo nó de adjacência com o ID especificado.
 *
 * Esta função aloca memória para um novo nó de adjacência e define o ID especificado.
 *
 * @param id O ID da adjacência a ser criada.
 * @return Um apontador para o novo nó de adjacência, se a alocação de memória for bem-sucedida; NULL caso contrário.
 */
Adjacent* NewAdjacent(int id, int peso)
{
	// Declaração de um apontador para o novo nó de adjacência
	Adjacent* adjacente;

	// Aloca memória para o novo nó de adjacência
	adjacente = (Adjacent*)malloc(sizeof(Adjacent));

	// Verifica se a alocação de memória foi bem-sucedida
	if (adjacente == NULL)
	{
		// Se a alocação de memória falhar, retorna NULL
		return NULL;
	}

	// Define o ID e peso da adjacência
	adjacente->id = id;
	adjacente->peso = peso;

	// Define o próximo nó de adjacência como NULL (ainda não há próximo nó)
	adjacente->next = NULL;

	// Retorna o apontador para o novo nó de adjacência
	return adjacente;
}

#pragma endregion


#pragma region Insere uma nova adjacência com o ID de destino especificado na lista de adjacências.
/**
 * @brief Insere uma nova adjacência com o ID de destino especificado na lista de adjacências.
 *
 * @param listaAdj O apontador para a lista de adjacências.
 * @param idDestino O ID de destino da nova adjacência a ser inserida.
 * @return Um apontador para a lista de adjacências atualizada após a inserção.
 */
Adjacent* InsertAdj(Adjacent* listaAdj, int idDestino, int peso)
{
	// Declaração do apontador para a nova adjacência
	Adjacent* newAdj;

	// Se o peso for zero, não inserir a adjacência
	if (peso == 0)
	{
		return listaAdj;
	}

	// Cria uma nova adjacência com o ID de destino especificado
	if ((newAdj = NewAdjacent(idDestino, peso)) == NULL)
	{
		// Se a criação da nova adjacência falhar, retorna a lista de adjacências sem modificações
		return listaAdj;
	}

	// Verifica se a lista de adjacências é vazia
	if (listaAdj == NULL)
	{
		// Se a lista de adjacências for vazia, a nova adjacência se torna o primeiro nó
		listaAdj = newAdj;
	}
	else
	{
		// Caso contrário, encontra o último nó da lista de adjacências
		Adjacent* aux = listaAdj;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		// Insere a nova adjacência no final da lista
		aux->next = newAdj;
	}

	// Retorna o apontador para a lista de adjacências atualizada após a inserção
	return listaAdj;
}

#pragma endregion


#pragma region Liberta a memória alocada para um nó de adjacência.
/**
 * @brief Liberta a memória alocada para um nó de adjacência.
 *
 * @param ptAdjacent O apontador para o nó de adjacência a ser liberado.
 * @return true se a memória for libertada com sucesso; false caso contrário.
 */
bool DestroyAdjacent(Adjacent* ptAdjacent)
{
	// Verifica se o apontador para o nó de adjacência é nulo
	if (ptAdjacent == NULL)
	{
		// Se for nulo, não há nada para liberar, então retorna false
		return false;
	}

	// Liberta a memória alocada para o nó de adjacência
	free(ptAdjacent);

	// Retorna true para indicar que a memória foi liberada com sucesso
	return true;
}

#pragma endregion


#pragma region Remove um nó de adjacência com o código especificado de uma lista ligada de adjacências.
/**
 * @brief Remove um nó de adjacência com o código especificado de uma lista ligada de adjacências.
 *
 * @param listAdj O apontador para o início da lista de adjacências.
 * @param codAdj O código da adjacência a ser removida.
 * @param res O apontador para uma variável que armazenará o resultado da operação.
 * @return O apontador atualizado para o início da lista de adjacências após a remoção.
 */
Adjacent* DeleteAdj(Adjacent* listAdj, int codAdj, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de adjacências é vazia
	if (listAdj == NULL)
	{
		// Se for vazia, retorna NULL, pois não há nada para remover
		return NULL;
	}

	// Inicializa apontadores auxiliares para percorrer a lista de adjacências
	Adjacent* aux = listAdj;
	Adjacent* ant = NULL;

	// Percorre a lista até encontrar o nó de adjacência com o código especificado
	while (aux != NULL && aux->id != codAdj)
	{
		ant = aux;
		aux = aux->next;
	}

	// Verifica se o nó de adjacência com o código especificado foi encontrado
	if (aux == NULL)
	{
		// Se não foi encontrado, retorna a lista de adjacências sem modificações
		return listAdj;
	}

	// Remove o nó de adjacência encontrado
	if (ant == NULL)
	{
		// Se o nó de adjacência a ser removido for o primeiro da lista
		listAdj = aux->next;
	}
	else
	{
		// Se o nó de adjacência a ser removido estiver no meio ou no final da lista
		ant->next = aux->next;
	}

	// Liberta a memória alocada para o nó de adjacência removido
	free(aux);

	// Define o resultado como verdadeiro, pois a remoção foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o início da lista de adjacências
	return listAdj;
}

#pragma endregion


#pragma region Remove todos os nós de adjacência de uma lista ligada de adjacências.
/**
 * @brief Remove todos os nós de adjacência de uma lista ligada de adjacências.
 *
 * @param listaAdj O apontador para o início da lista de adjacências a serem removidas.
 * @param res O apontador para uma variável que armazenará o resultado da operação.
 * @return O apontador atualizado para o início da lista de adjacências após a remoção de todos os nós.
 */
Adjacent* DeleteAllAdj(Adjacent* listaAdj, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de adjacências é vazia
	if (listaAdj == NULL)
	{
		// Se for vazia, não há nada para remover, então retorna NULL
		return NULL;
	}

	// Inicializa um apontador auxiliar para percorrer a lista de adjacências
	Adjacent* aux = listaAdj;

	// Percorre a lista de adjacências e remove cada nó
	while (aux)
	{
		// Armazena o próximo nó antes de destruir o nó atual
		Adjacent* next = aux->next;
		DestroyAdjacent(aux);
		aux = next;
	}

	// Define o resultado como verdadeiro, pois a remoção foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o início da lista de adjacências (que é NULL, pois todos os nós foram removidos)
	return NULL;
}

#pragma endregion


