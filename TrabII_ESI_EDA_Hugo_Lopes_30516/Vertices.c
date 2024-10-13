/**
 * @file   Vertices.c
 * @author Hugo Lopes_30516
 *
 * @brief Definição das funções relacionadas a vértices.
 *
 * Este ficheiro contém as definições das funções relacionadas à criação, manipulação e remoção de vértices
 * em uma estrutura de grafo.
 *
 * @date  Maio 2024
 */
#include <stdio.h>
#include<malloc.h>
#include <stdbool.h>
#include"Vertices.h"
#include"VerticesAdjacent.h"



#pragma region Cria um novo vértice com o ID especificado.
 /**
 * @brief Cria um novo vértice com o ID especificado.
 *
 * @param id O ID do vértice a ser criado.
 * @param res Apontador para uma variável bool onde será armazenado o resultado da operação.
 * @return Um apontador para o novo vértice criado, ou NULL se a alocação de memória falhar.
 */
Node* CreateVertice(int id, bool* res) 
{
	*res = false;

	// Aloca memória para o novo vértice
	Node* aux = (Node*)malloc(sizeof(Node));

	// Verifica se a alocação de memória foi bem-sucedida
	if (aux == NULL) 
	{
		// Se a alocação falhou, retorna NULL
		return NULL;
	}

	aux->id = id;

	// Inicializa os campos do vértice
	aux->nextVertice = NULL;
	aux->nextAdjacent = NULL;

	// Define res como verdadeiro para indicar sucesso
	*res = true;

	// Retorna o apontador para o novo vértice
	return aux;
}



#pragma endregion


#pragma region Liberta a memória alocada para um vértice.
/**
* @brief Liberta a memória alocada para um vértice.
*
* @param ptNode Um apontador para o vértice a ser destruído.
* @return true se a operação foi bem - sucedida, false caso contrário.
*/
bool DestroiVertice(Node* ptNode)
{
	// Verifica se o apontador para o vértice é válido
	if (ptNode == NULL)
	{
		// Se o apontador for nulo, não há nada para destruir, então retorna false
		return false;
	}

	
	// Liberta a memória alocada para o vértice
	free(ptNode);

	// Retorna true para indicar que a operação foi bem-sucedida
	return true;
}


#pragma endregion


#pragma region  Localiza um vértice com o ID especificado na lista ligada de vértices.
/**
 * @brief Localiza um vértice com o ID especificado na lista ligada de vértices.
 *
 * @param inicio O apontador para o início da lista ligada de vértices.
 * @param id O ID do vértice a ser localizado.
 * @return Um apontador para o vértice com o ID especificado, se encontrado; NULL caso contrário.
 */
Node* WhereIsVertice(Node* inicio, int id)
{
	// Verifica se o apontador para o início da lista é válido
	if (inicio == NULL)
	{
		// Se a lista estiver vazia, retorna NULL
		return NULL;
	}

	// Inicia uma variável auxiliar para percorrer a lista
	Node* aux = inicio;

	// Percorre a lista enquanto não atingir o final
	while (aux)
	{
		// Verifica se o ID do vértice atual é igual ao ID especificado
		if (aux->id == id)
		{
			// Se encontrar o vértice com o ID especificado, retorna o apontador para ele
			return aux;
		}

		// Avança para o próximo vértice na lista
		aux = aux->nextVertice;
	}

	// Se não encontrar o vértice com o ID especificado, retorna NULL
	return NULL;
}
#pragma endregion 


#pragma region Verifica se um vértice com o ID especificado existe na lista ligada de vértices.
/**
 * @brief Verifica se um vértice com o ID especificado existe na lista ligada de vértices.
 *
 * @param listaDeVertices O apontador para o início da lista ligada de vértices.
 * @param id O ID do vértice a ser verificado.
 * @return true se um vértice com o ID especificado existe na lista; false caso contrário.
 */
bool ExistVertice(Node* listaDeVertices, int id)
{
	// Verifica se a lista de vértices é vazia
	if (listaDeVertices == NULL)
	{
		// Se a lista estiver vazia, não pode haver vértices, então retorna false
		return false;
	}

	// Inicia uma variável auxiliar para percorrer a lista de vértices
	Node* aux = listaDeVertices;

	// Percorre a lista enquanto não atingir o final
	while (aux)
	{
		// Verifica se o ID do vértice atual é igual ao ID especificado
		if (aux->id == id)
		{
			// Se encontrar um vértice com o ID especificado, retorna true
			return true;
		}

		// Avança para o próximo vértice na lista
		aux = aux->nextVertice;
	}

	// Se não encontrar um vértice com o ID especificado, retorna false
	return false;
}
#pragma endregion


#pragma region Insere um novo vértice em uma lista ligada de vértices.
/**
 * @brief Insere um novo vértice numa lista ligada de vértices.
 *
 * @param vertices O apontador para o início da lista de vértices.
 * @param novo O apontador para o novo vértice a ser inserido.
 * @param res O apontador para uma variável que armazenará o resultado da operação.
 * @return O apontador atualizado para o início da lista de vértices.
 */
Node* InsertVertice(Node* vertices, Node* novo, bool* res) 
{
	// Verifica se o vértice a ser inserido é nulo
	if (novo == NULL) 
	{
		if (res != NULL) *res = false;
		
		return vertices; // Retorna a lista sem alteração
	}

	// Verifica se o vértice com o mesmo ID já existe na lista
	if (ExistVertice(vertices, novo->id)) 
	{
		if (res != NULL) *res = false;
		
		return vertices; // Retorna a lista sem realizar a inserção
	}

	// Insere o novo vértice na lista ordenada
	Node* ant = NULL;
	Node* aux = vertices;
	while (aux != NULL && aux->id < novo->id) 
	{
		ant = aux;
		aux = aux->nextVertice;
	}

	// Define o resultado da inserção como verdadeiro
	if (res != NULL) *res = true;
	

	// Insere o novo vértice no lugar correto
	if (ant == NULL) 
	{
		// Inserção no início da lista
		novo->nextVertice = vertices;
		vertices = novo;
	}
	else 
	{
		// Inserção no meio ou fim da lista
		novo->nextVertice = aux;
		ant->nextVertice = novo;
	}

	return vertices;
}
#pragma endregion


#pragma region Remove um vértice com o código especificado de uma lista ligada de vértices.
/**
 * @brief Remove um vértice com o código especificado de uma lista ligada de vértices.
 *
 * @param vertices O apontador para o início da lista de vértices.
 * @param codVertice O código do vértice a ser removido.
 * @param res O apontador para uma variável que armazenará o resultado da operação.
 * @return O apontador atualizado para o início da lista de vértices após a remoção.
 */
Node* DeleteVertice(Node* vertices, int codVertice, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de vértices é vazia
	if (vertices == NULL) return NULL;


	// Inicializa os apontadores auxiliares para percorrer a lista de vértices
	Node* aux = vertices;
	Node* ant = NULL;

	// Percorre a lista até encontrar o vértice com o código especificado
	while (aux->id != codVertice)
	{
		ant = aux;
		aux = aux->nextVertice;
	}
	//não existe	
	if (!aux) return vertices;
		
	

	
	if (ant == NULL)
	{
			aux->nextAdjacent = DeleteAllAdj(aux->nextAdjacent, res);
			// Se a remoção dos vértices adjacentes falhar, retorna a lista sem modificação
		if (*res == false) return vertices;

		vertices = aux->nextVertice;
	}
	// Se o vértice a ser removido estiver no meio ou no final da lista
	else 
		ant->nextVertice = aux->nextVertice;
	
		

	// Liberta a memória alocada para o vértice removido
	DestroiVertice(aux);

	// Define o resultado como verdadeiro, pois a remoção foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o início da lista de vértices
	return vertices;
}
#pragma endregion


#pragma region Remove todas as adjacências com o código especificado de todos os vértices em uma lista ligada de vértices.
/**
 * @brief Remove todas as adjacências com o código especificado de todos os vértices numa lista ligada de vértices.
 *
 * @param vertices O apontador para o início da lista de vértices.
 * @param codAdj O código da adjacência a ser removida de todos os vértices.
 * @param res O apontador para uma variável que armazenará o resultado da operação.
 * @return O apontador atualizado para o início da lista de vértices após a remoção das adjacências.
 */
Node* DeleteAllAdjVert(Node* vertices, int codAdj, bool* res)
{
	// Inicializa o resultado como falso
	*res = false;

	// Verifica se a lista de vértices é vazia
	if (vertices == NULL) return NULL;
	

	// Inicializa um apontador auxiliar para percorrer a lista de vértices
	Node* aux = vertices;

	// Percorre a lista de vértices e remove as adjacências com o código especificado de cada vértice
	while (aux)
	{
		// Remove as adjacências com o código especificado do vértice atual
		aux->nextAdjacent = DeleteAdj(aux->nextAdjacent, codAdj, res);

		// Avança para o próximo vértice na lista
		aux = aux->nextVertice;
	}

	// Define o resultado como verdadeiro, pois a remoção das adjacências foi bem-sucedida
	*res = true;

	// Retorna o apontador atualizado para o início da lista de vértices
	return vertices;
}
#pragma endregion


#pragma region Mostra os vértices e suas adjacências no grafo.
/**
 * @brief Mostra os vértices e suas adjacências no grafo.
 *
 * @param graph O apontador para o grafo a ser mostrado.
 * @return true se o grafo não estiver vazio e for mostrado com sucesso; false caso contrário.
 */
bool ShowGraph(Node* graph)
{
	// Verifica se o grafo está vazio
	if (graph == NULL)
	{
		// Se estiver vazio, imprime uma mensagem indicando que o grafo está vazio e retorna false
		printf("O grafo está vazio.\n");
		return false;
	}

	// Inicializa um apontador para percorrer os vértices do grafo
	Node* current = graph;

	// Percorre os vértices do grafo
	while (current != NULL)
	{
		// Imprime o ID do vértice atual
		printf("Vértice %d:\n", current->id);

		// Inicializa um apontador para percorrer as adjacências do vértice atual
		Adjacent* currentAdjacent = current->nextAdjacent;

		// Percorre as adjacências do vértice atual
		while (currentAdjacent != NULL)
		{
			printf("\t\t");
			// Imprime o ID da adjacência atual
			printf("Adjacente:%d(peso:%d)\n", currentAdjacent->id,currentAdjacent->peso);

			// Avança para a próxima adjacência
			currentAdjacent = currentAdjacent->next;

		}

		// Imprime uma quebra de linha para separar os vértices
		printf("\n");

		// Avança para o próximo vértice no grafo
		current = current->nextVertice;
	}
	printf("**********************************************\n");
	printf("\n");
	// Retorna true para indicar que o grafo foi mostrado com sucesso
	return true;
}

#pragma endregion


