/**
 * @file   VerticesAdjacent.c
 * @author Hugo Lopes_30516
 *
 * @brief Defini��o das fun��es relacionadas a v�rtices adjacentes.
 *
 * Este ficheiro cont�m a implementa��o das fun��es respons�veis por opera��es
 * relacionadas a v�rtices adjacentes em grafos.
 *
 * @date   May 2024
 */

#include<malloc.h>
#include <stdbool.h>
#include"VerticesAdjacent.h"


#pragma region Cria um novo n� de adjac�ncia com o ID especificado.
 /**
 * @brief Cria um novo n� de adjac�ncia com o ID especificado.
 *
 * Esta fun��o aloca mem�ria para um novo n� de adjac�ncia e define o ID especificado.
 *
 * @param id O ID da adjac�ncia a ser criada.
 * @return Um apontador para o novo n� de adjac�ncia, se a aloca��o de mem�ria for bem-sucedida; NULL caso contr�rio.
 */
Adjacent* NewAdjacent(int id, int peso)
{
	// Declara��o de um apontador para o novo n� de adjac�ncia
	Adjacent* adjacente;

	// Aloca mem�ria para o novo n� de adjac�ncia
	adjacente = (Adjacent*)malloc(sizeof(Adjacent));

	// Verifica se a aloca��o de mem�ria foi bem-sucedida
	if (adjacente == NULL)
	{
		// Se a aloca��o de mem�ria falhar, retorna NULL
		return NULL;
	}

	// Define o ID e peso da adjac�ncia
	adjacente->id = id;
	adjacente->peso = peso;

	// Define o pr�ximo n� de adjac�ncia como NULL (ainda n�o h� pr�ximo n�)
	adjacente->next = NULL;

	// Retorna o apontador para o novo n� de adjac�ncia
	return adjacente;
}

#pragma endregion


#pragma region Insere uma nova adjac�ncia com o ID de destino especificado na lista de adjac�ncias.
/**
 * @brief Insere uma nova adjac�ncia com o ID de destino especificado na lista de adjac�ncias.
 *
 * @param listaAdj O apontador para a lista de adjac�ncias.
 * @param idDestino O ID de destino da nova adjac�ncia a ser inserida.
 * @return Um apontador para a lista de adjac�ncias atualizada ap�s a inser��o.
 */
Adjacent* InsertAdj(Adjacent* listaAdj, int idDestino, int peso)
{
	// Declara��o do apontador para a nova adjac�ncia
	Adjacent* newAdj;

	// Se o peso for zero, n�o inserir a adjac�ncia
	if (peso == 0)
	{
		return listaAdj;
	}

	// Cria uma nova adjac�ncia com o ID de destino especificado
	if ((newAdj = NewAdjacent(idDestino, peso)) == NULL)
	{
		// Se a cria��o da nova adjac�ncia falhar, retorna a lista de adjac�ncias sem modifica��es
		return listaAdj;
	}

	// Verifica se a lista de adjac�ncias � vazia
	if (listaAdj == NULL)
	{
		// Se a lista de adjac�ncias for vazia, a nova adjac�ncia se torna o primeiro n�
		listaAdj = newAdj;
	}
	else
	{
		// Caso contr�rio, encontra o �ltimo n� da lista de adjac�ncias
		Adjacent* aux = listaAdj;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		// Insere a nova adjac�ncia no final da lista
		aux->next = newAdj;
	}

	// Retorna o apontador para a lista de adjac�ncias atualizada ap�s a inser��o
	return listaAdj;
}

#pragma endregion


#pragma region Liberta a mem�ria alocada para um n� de adjac�ncia.
/**
 * @brief Liberta a mem�ria alocada para um n� de adjac�ncia.
 *
 * @param ptAdjacent O apontador para o n� de adjac�ncia a ser liberado.
 * @return true se a mem�ria for libertada com sucesso; false caso contr�rio.
 */
bool DestroyAdjacent(Adjacent* ptAdjacent)
{
	// Verifica se o apontador para o n� de adjac�ncia � nulo
	if (ptAdjacent == NULL)
	{
		// Se for nulo, n�o h� nada para liberar, ent�o retorna false
		return false;
	}

	// Liberta a mem�ria alocada para o n� de adjac�ncia
	free(ptAdjacent);

	// Retorna true para indicar que a mem�ria foi liberada com sucesso
	return true;
}

#pragma endregion


#pragma region Remove um n� de adjac�ncia com o c�digo especificado de uma lista ligada de adjac�ncias.
/**
 * @brief Remove um n� de adjac�ncia com o c�digo especificado de uma lista ligada de adjac�ncias.
 *
 * @param listAdj O apontador para o in�cio da lista de adjac�ncias.
 * @param codAdj O c�digo da adjac�ncia a ser removida.
 * @param res O apontador para uma vari�vel que armazenar� o resultado da opera��o.
 * @return O apontador atualizado para o in�cio da lista de adjac�ncias ap�s a remo��o.
 */
Adjacent* DeleteAdj(Adjacent* listAdj, int codAdj, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de adjac�ncias � vazia
	if (listAdj == NULL)
	{
		// Se for vazia, retorna NULL, pois n�o h� nada para remover
		return NULL;
	}

	// Inicializa apontadores auxiliares para percorrer a lista de adjac�ncias
	Adjacent* aux = listAdj;
	Adjacent* ant = NULL;

	// Percorre a lista at� encontrar o n� de adjac�ncia com o c�digo especificado
	while (aux != NULL && aux->id != codAdj)
	{
		ant = aux;
		aux = aux->next;
	}

	// Verifica se o n� de adjac�ncia com o c�digo especificado foi encontrado
	if (aux == NULL)
	{
		// Se n�o foi encontrado, retorna a lista de adjac�ncias sem modifica��es
		return listAdj;
	}

	// Remove o n� de adjac�ncia encontrado
	if (ant == NULL)
	{
		// Se o n� de adjac�ncia a ser removido for o primeiro da lista
		listAdj = aux->next;
	}
	else
	{
		// Se o n� de adjac�ncia a ser removido estiver no meio ou no final da lista
		ant->next = aux->next;
	}

	// Liberta a mem�ria alocada para o n� de adjac�ncia removido
	free(aux);

	// Define o resultado como verdadeiro, pois a remo��o foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o in�cio da lista de adjac�ncias
	return listAdj;
}

#pragma endregion


#pragma region Remove todos os n�s de adjac�ncia de uma lista ligada de adjac�ncias.
/**
 * @brief Remove todos os n�s de adjac�ncia de uma lista ligada de adjac�ncias.
 *
 * @param listaAdj O apontador para o in�cio da lista de adjac�ncias a serem removidas.
 * @param res O apontador para uma vari�vel que armazenar� o resultado da opera��o.
 * @return O apontador atualizado para o in�cio da lista de adjac�ncias ap�s a remo��o de todos os n�s.
 */
Adjacent* DeleteAllAdj(Adjacent* listaAdj, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de adjac�ncias � vazia
	if (listaAdj == NULL)
	{
		// Se for vazia, n�o h� nada para remover, ent�o retorna NULL
		return NULL;
	}

	// Inicializa um apontador auxiliar para percorrer a lista de adjac�ncias
	Adjacent* aux = listaAdj;

	// Percorre a lista de adjac�ncias e remove cada n�
	while (aux)
	{
		// Armazena o pr�ximo n� antes de destruir o n� atual
		Adjacent* next = aux->next;
		DestroyAdjacent(aux);
		aux = next;
	}

	// Define o resultado como verdadeiro, pois a remo��o foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o in�cio da lista de adjac�ncias (que � NULL, pois todos os n�s foram removidos)
	return NULL;
}

#pragma endregion


