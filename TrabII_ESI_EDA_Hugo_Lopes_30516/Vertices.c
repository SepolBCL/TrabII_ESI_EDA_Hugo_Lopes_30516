/**
 * @file   Vertices.c
 * @author Hugo Lopes_30516
 *
 * @brief Defini��o das fun��es relacionadas a v�rtices.
 *
 * Este ficheiro cont�m as defini��es das fun��es relacionadas � cria��o, manipula��o e remo��o de v�rtices
 * em uma estrutura de grafo.
 *
 * @date  Maio 2024
 */
#include <stdio.h>
#include<malloc.h>
#include <stdbool.h>
#include"Vertices.h"
#include"VerticesAdjacent.h"



#pragma region Cria um novo v�rtice com o ID especificado.
 /**
 * @brief Cria um novo v�rtice com o ID especificado.
 *
 * @param id O ID do v�rtice a ser criado.
 * @param res Apontador para uma vari�vel bool onde ser� armazenado o resultado da opera��o.
 * @return Um apontador para o novo v�rtice criado, ou NULL se a aloca��o de mem�ria falhar.
 */
Node* CreateVertice(int id, bool* res) 
{
	*res = false;

	// Aloca mem�ria para o novo v�rtice
	Node* aux = (Node*)malloc(sizeof(Node));

	// Verifica se a aloca��o de mem�ria foi bem-sucedida
	if (aux == NULL) 
	{
		// Se a aloca��o falhou, retorna NULL
		return NULL;
	}

	aux->id = id;

	// Inicializa os campos do v�rtice
	aux->nextVertice = NULL;
	aux->nextAdjacent = NULL;

	// Define res como verdadeiro para indicar sucesso
	*res = true;

	// Retorna o apontador para o novo v�rtice
	return aux;
}



#pragma endregion


#pragma region Liberta a mem�ria alocada para um v�rtice.
/**
* @brief Liberta a mem�ria alocada para um v�rtice.
*
* @param ptNode Um apontador para o v�rtice a ser destru�do.
* @return true se a opera��o foi bem - sucedida, false caso contr�rio.
*/
bool DestroiVertice(Node* ptNode)
{
	// Verifica se o apontador para o v�rtice � v�lido
	if (ptNode == NULL)
	{
		// Se o apontador for nulo, n�o h� nada para destruir, ent�o retorna false
		return false;
	}

	
	// Liberta a mem�ria alocada para o v�rtice
	free(ptNode);

	// Retorna true para indicar que a opera��o foi bem-sucedida
	return true;
}


#pragma endregion


#pragma region  Localiza um v�rtice com o ID especificado na lista ligada de v�rtices.
/**
 * @brief Localiza um v�rtice com o ID especificado na lista ligada de v�rtices.
 *
 * @param inicio O apontador para o in�cio da lista ligada de v�rtices.
 * @param id O ID do v�rtice a ser localizado.
 * @return Um apontador para o v�rtice com o ID especificado, se encontrado; NULL caso contr�rio.
 */
Node* WhereIsVertice(Node* inicio, int id)
{
	// Verifica se o apontador para o in�cio da lista � v�lido
	if (inicio == NULL)
	{
		// Se a lista estiver vazia, retorna NULL
		return NULL;
	}

	// Inicia uma vari�vel auxiliar para percorrer a lista
	Node* aux = inicio;

	// Percorre a lista enquanto n�o atingir o final
	while (aux)
	{
		// Verifica se o ID do v�rtice atual � igual ao ID especificado
		if (aux->id == id)
		{
			// Se encontrar o v�rtice com o ID especificado, retorna o apontador para ele
			return aux;
		}

		// Avan�a para o pr�ximo v�rtice na lista
		aux = aux->nextVertice;
	}

	// Se n�o encontrar o v�rtice com o ID especificado, retorna NULL
	return NULL;
}
#pragma endregion 


#pragma region Verifica se um v�rtice com o ID especificado existe na lista ligada de v�rtices.
/**
 * @brief Verifica se um v�rtice com o ID especificado existe na lista ligada de v�rtices.
 *
 * @param listaDeVertices O apontador para o in�cio da lista ligada de v�rtices.
 * @param id O ID do v�rtice a ser verificado.
 * @return true se um v�rtice com o ID especificado existe na lista; false caso contr�rio.
 */
bool ExistVertice(Node* listaDeVertices, int id)
{
	// Verifica se a lista de v�rtices � vazia
	if (listaDeVertices == NULL)
	{
		// Se a lista estiver vazia, n�o pode haver v�rtices, ent�o retorna false
		return false;
	}

	// Inicia uma vari�vel auxiliar para percorrer a lista de v�rtices
	Node* aux = listaDeVertices;

	// Percorre a lista enquanto n�o atingir o final
	while (aux)
	{
		// Verifica se o ID do v�rtice atual � igual ao ID especificado
		if (aux->id == id)
		{
			// Se encontrar um v�rtice com o ID especificado, retorna true
			return true;
		}

		// Avan�a para o pr�ximo v�rtice na lista
		aux = aux->nextVertice;
	}

	// Se n�o encontrar um v�rtice com o ID especificado, retorna false
	return false;
}
#pragma endregion


#pragma region Insere um novo v�rtice em uma lista ligada de v�rtices.
/**
 * @brief Insere um novo v�rtice numa lista ligada de v�rtices.
 *
 * @param vertices O apontador para o in�cio da lista de v�rtices.
 * @param novo O apontador para o novo v�rtice a ser inserido.
 * @param res O apontador para uma vari�vel que armazenar� o resultado da opera��o.
 * @return O apontador atualizado para o in�cio da lista de v�rtices.
 */
Node* InsertVertice(Node* vertices, Node* novo, bool* res) 
{
	// Verifica se o v�rtice a ser inserido � nulo
	if (novo == NULL) 
	{
		if (res != NULL) *res = false;
		
		return vertices; // Retorna a lista sem altera��o
	}

	// Verifica se o v�rtice com o mesmo ID j� existe na lista
	if (ExistVertice(vertices, novo->id)) 
	{
		if (res != NULL) *res = false;
		
		return vertices; // Retorna a lista sem realizar a inser��o
	}

	// Insere o novo v�rtice na lista ordenada
	Node* ant = NULL;
	Node* aux = vertices;
	while (aux != NULL && aux->id < novo->id) 
	{
		ant = aux;
		aux = aux->nextVertice;
	}

	// Define o resultado da inser��o como verdadeiro
	if (res != NULL) *res = true;
	

	// Insere o novo v�rtice no lugar correto
	if (ant == NULL) 
	{
		// Inser��o no in�cio da lista
		novo->nextVertice = vertices;
		vertices = novo;
	}
	else 
	{
		// Inser��o no meio ou fim da lista
		novo->nextVertice = aux;
		ant->nextVertice = novo;
	}

	return vertices;
}
#pragma endregion


#pragma region Remove um v�rtice com o c�digo especificado de uma lista ligada de v�rtices.
/**
 * @brief Remove um v�rtice com o c�digo especificado de uma lista ligada de v�rtices.
 *
 * @param vertices O apontador para o in�cio da lista de v�rtices.
 * @param codVertice O c�digo do v�rtice a ser removido.
 * @param res O apontador para uma vari�vel que armazenar� o resultado da opera��o.
 * @return O apontador atualizado para o in�cio da lista de v�rtices ap�s a remo��o.
 */
Node* DeleteVertice(Node* vertices, int codVertice, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de v�rtices � vazia
	if (vertices == NULL) return NULL;


	// Inicializa os apontadores auxiliares para percorrer a lista de v�rtices
	Node* aux = vertices;
	Node* ant = NULL;

	// Percorre a lista at� encontrar o v�rtice com o c�digo especificado
	while (aux->id != codVertice)
	{
		ant = aux;
		aux = aux->nextVertice;
	}
	//n�o existe	
	if (!aux) return vertices;
		
	

	
	if (ant == NULL)
	{
			aux->nextAdjacent = DeleteAllAdj(aux->nextAdjacent, res);
			// Se a remo��o dos v�rtices adjacentes falhar, retorna a lista sem modifica��o
		if (*res == false) return vertices;

		vertices = aux->nextVertice;
	}
	// Se o v�rtice a ser removido estiver no meio ou no final da lista
	else 
		ant->nextVertice = aux->nextVertice;
	
		

	// Liberta a mem�ria alocada para o v�rtice removido
	DestroiVertice(aux);

	// Define o resultado como verdadeiro, pois a remo��o foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o in�cio da lista de v�rtices
	return vertices;
}
#pragma endregion


#pragma region Remove todas as adjac�ncias com o c�digo especificado de todos os v�rtices em uma lista ligada de v�rtices.
/**
 * @brief Remove todas as adjac�ncias com o c�digo especificado de todos os v�rtices numa lista ligada de v�rtices.
 *
 * @param vertices O apontador para o in�cio da lista de v�rtices.
 * @param codAdj O c�digo da adjac�ncia a ser removida de todos os v�rtices.
 * @param res O apontador para uma vari�vel que armazenar� o resultado da opera��o.
 * @return O apontador atualizado para o in�cio da lista de v�rtices ap�s a remo��o das adjac�ncias.
 */
Node* DeleteAllAdjVert(Node* vertices, int codAdj, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de v�rtices � vazia
	if (vertices == NULL) return NULL;
	

	// Inicializa um apontador auxiliar para percorrer a lista de v�rtices
	Node* aux = vertices;

	// Percorre a lista de v�rtices e remove as adjac�ncias com o c�digo especificado de cada v�rtice
	while (aux)
	{
		// Remove as adjac�ncias com o c�digo especificado do v�rtice atual
		aux->nextAdjacent = DeleteAdj(aux->nextAdjacent, codAdj, res);

		// Avan�a para o pr�ximo v�rtice na lista
		aux = aux->nextVertice;
	}

	// Define o resultado como verdadeiro, pois a remo��o das adjac�ncias foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o in�cio da lista de v�rtices
	return vertices;
}
#pragma endregion


#pragma region Mostra os v�rtices e suas adjac�ncias no grafo.
/**
 * @brief Mostra os v�rtices e suas adjac�ncias no grafo.
 *
 * @param graph O apontador para o grafo a ser mostrado.
 * @return true se o grafo n�o estiver vazio e for mostrado com sucesso; false caso contr�rio.
 */
bool ShowGraph(Node* graph)
{
	// Verifica se o grafo est� vazio
	if (graph == NULL)
	{
		// Se estiver vazio, imprime uma mensagem indicando que o grafo est� vazio e retorna false
		printf("O grafo est� vazio.\n");
		return false;
	}

	// Inicializa um apontador para percorrer os v�rtices do grafo
	Node* current = graph;

	// Percorre os v�rtices do grafo
	while (current != NULL)
	{
		// Imprime o ID do v�rtice atual
		printf("V�rtice %d:\n", current->id);

		// Inicializa um apontador para percorrer as adjac�ncias do v�rtice atual
		Adjacent* currentAdjacent = current->nextAdjacent;

		// Percorre as adjac�ncias do v�rtice atual
		while (currentAdjacent != NULL)
		{
			printf("\t\t");
			// Imprime o ID da adjac�ncia atual
			printf("Adjacente:%d(peso:%d)\n", currentAdjacent->id,currentAdjacent->peso);

			// Avan�a para a pr�xima adjac�ncia
			currentAdjacent = currentAdjacent->next;

		}

		// Imprime uma quebra de linha para separar os v�rtices
		printf("\n");

		// Avan�a para o pr�ximo v�rtice no grafo
		current = current->nextVertice;
	}
	printf("**********************************************\n");
	printf("\n");
	// Retorna true para indicar que o grafo foi mostrado com sucesso
	return true;
}

#pragma endregion


