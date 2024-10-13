/**
 * @file   Graph.c
 * @brief  Implementa��o das fun��es relacionadas a grafos.
 *
 * Este ficheiro cont�m a implementa��o das fun��es necess�rias para manipular
 * grafos, incluindo a cria��o, manipula��o e libera��o de mem�ria.
 *
 * @date   May 2024
 * @author Hugo Lopes_30516
 */


#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include <stdbool.h>
#include"VerticesAdjacent.h"
#include"Vertices.h"
#include"Graph.h"
#include"IN.h"


#pragma region Cria um novo grafo.
/**
* Cria um novo grafo.
*
* @param totV O n�mero total de v�rtices do grafo.
* @param res Apontador para um booleano que indica se a cria��o foi bem - sucedida.
* @return Um apontador para o novo grafo criado, ou NULL se a aloca��o de mem�ria falhar ou totV for inv�lido.
*/
Graph* CreateGraph(int *totV, bool* res)
{
   
    *res = false;
    // Verifica se o n�mero total de v�rtices � v�lido
    if ((*totV) <= 0) return NULL;
    

    // Aloca mem�ria para o grafo
    Graph* aux = (Graph*)malloc(sizeof(Graph));

    // Verifica se a aloca��o de mem�ria foi bem-sucedida
    if (aux == NULL) return NULL;
    

    // Inicializa��o do grafo
    aux->inicioGraph = NULL;
    aux->numeroVertices = 0;
    aux->totVertices = (*totV);

    *res = true; // Indica que a cria��o do grafo foi bem-sucedida
    return aux; // Retorna o grafo criado
}
#pragma endregion


#pragma region Insere um novo v�rtice no grafo.
/**
*Insere um novo v�rtice no grafo.
*
* @param G O grafo no qual o v�rtice ser� inserido.
* @param id O ID do v�rtice a ser inserido.
* @param res Um apontador para um inteiro que indica o resultado da opera��o.
* Se a opera��o for bem - sucedida, res deve ser 1. Caso contr�rio,
* deve conter um c�digo de erro espec�fico.
* @return O apontador para o grafo atualizado, ou NULL em caso de erro.
*/
Graph* InsertVertGraph(Graph* G, Node* new, bool* res)
{
    
    *res = false;

    // Verifica se o grafo � v�lido
    if (G == NULL)
    {
        *res = false; // C�digo de erro: Grafo n�o v�lido
        return NULL;
    }

    // Verifica se o v�rtice j� existe no grafo
    if (ExistVertice(G->inicioGraph, new->id))
    {
        *res = false; // C�digo de erro: V�rtice j� existe no grafo
        return G;
    }

    // Insere o v�rtice no grafo
    G->inicioGraph = InsertVertice(G->inicioGraph, new, res);
    if (G->inicioGraph == NULL)
    {
        *res = false; // C�digo de erro: Falha ao inserir v�rtice no grafo
        return G;
    }
    else G->numeroVertices++; // Incrementa o n�mero de v�rtices no grafo
    

    // Retorna o grafo atualizado
    return G;
}
#pragma endregion


#pragma region Insere uma adjac�ncia entre dois v�rtices no grafo.
/**
 * Insere uma adjac�ncia entre dois v�rtices no grafo.
 *
 * @param G O grafo no qual a adjac�ncia ser� inserida.
 * @param idOrigin O ID do v�rtice de origem.
 * @param idDestiny O ID do v�rtice de destino.
 * @param res Um apontador para um booleano que indica se a opera��o foi bem-sucedida.
 * @return O apontador para o grafo atualizado, ou NULL em caso de erro.
 */
Graph* InsertAdjaGraph(Graph* G, int idOrigin, int idDestiny,int peso, bool* res)
{
    *res = false;
    // Verifica se o grafo � nulo ou se a lista de v�rtices est� vazia
    if (G == NULL || G->inicioGraph == NULL) return NULL;

    // Encontra os n�s correspondentes no grafo
    Node* originNode = WhereIsVertice(G->inicioGraph, idOrigin);
    if (originNode == NULL) return G;
    Node* destinyNode = WhereIsVertice(G->inicioGraph, idDestiny);
    if (destinyNode == NULL) return G;

    // Insere a adjac�ncia
    originNode->nextAdjacent = InsertAdj(originNode->nextAdjacent, idDestiny,peso);

    *res = true;
    return G;
}
#pragma endregion


#pragma region Remove uma adjac�ncia entre dois v�rtices no grafo.
/**
 * Remove uma adjac�ncia entre dois v�rtices no grafo.
 *
 * @param G O grafo no qual a adjac�ncia ser� removida.
 * @param origin O ID do v�rtice de origem.
 * @param destiny O ID do v�rtice de destino.
 * @param res Um apontador para um booleano que indica se a opera��o foi bem-sucedida.
 * @return O apontador para o grafo atualizado, ou NULL em caso de erro.
 */
Graph* DeleteAdjGraph(Graph* G, int origin, int destiny, bool* res)
{
    *res = false;

    // Verifica se o grafo � nulo ou se a lista de v�rtices est� vazia
    if (G == NULL || G->inicioGraph == NULL) return NULL;

    // Encontra os n�s correspondentes no grafo
    Node* originNode = WhereIsVertice(G->inicioGraph, origin);
    if (originNode == NULL) return G;
    Node* destinyNode = WhereIsVertice(G->inicioGraph, destiny);
    if (destinyNode == NULL) return G;

    // Remove a adjac�ncia, se existir
    originNode->nextAdjacent = DeleteAdj(originNode->nextAdjacent, destiny,res);

    *res = true;
    return G;
}
#pragma endregion


#pragma region Encontra um v�rtice com o ID especificado em um grafo.
/**
 * Encontra um v�rtice com o ID especificado em um grafo.
 *
 * @param G O apontador para o grafo onde o v�rtice ser� procurado.
 * @param idVertice O ID do v�rtice a ser encontrado.
 * @return Um apontador para o v�rtice encontrado, se existir; NULL caso contr�rio.
 */
Graph* WhereIsVertGraph(Graph* G, int idVertice)
{
    // Verifica se o grafo � nulo
    if (G == NULL) return NULL;
    

    // Chama a fun��o WhereIsVertice para procurar o v�rtice na lista de v�rtices do grafo
    return (WhereIsVertice(G->inicioGraph, idVertice));
}

#pragma endregion


#pragma region Remove um v�rtice e todas as suas adjac�ncias de um grafo.
/**
 * Remove um v�rtice e todas as suas adjac�ncias de um grafo.
 *
 * @param g O apontador para o grafo onde o v�rtice ser� removido.
 * @param codVertice O c�digo do v�rtice a ser removido.
 * @param res O apontador para uma vari�vel que armazenar� o resultado da opera��o.
 * @return O apontador para o grafo atualizado ap�s a remo��o do v�rtice e suas adjac�ncias.
 */
Graph* DeleteVertGraph(Graph* G, int codVertice, bool* res)
{
    // Inicializa o resultado como falso
    *res = false;

    // Verifica se o grafo � nulo
    if (G == NULL) return NULL;

    // Remove o v�rtice da lista de v�rtices do grafo
    G->inicioGraph = DeleteVertice(G->inicioGraph, codVertice, res);

    // Remove todas as adjac�ncias relacionadas ao v�rtice removido
    G->inicioGraph = DeleteAllAdjVert(G->inicioGraph,codVertice, res);

    // Verifica se a remo��o foi bem-sucedida
    if (*res == true) G->numeroVertices--;
    

    // Retorna o apontador para o grafo atualizado ap�s a remo��o do v�rtice e suas adjac�ncias
    return G;
}

#pragma endregion


#pragma region Verifica se um v�rtice com o ID especificado existe em um grafo.
/**
 * Verifica se um v�rtice com o ID especificado existe em um grafo.
 *
 * @param inicio O apontador para o in�cio do grafo onde o v�rtice ser� procurado.
 * @param idVertice O ID do v�rtice a ser verificado.
 * @return true se o v�rtice existir no grafo; false caso contr�rio.
 */
bool ExistVertGraph(Graph* G, int idVertice)
{
    // Verifica se o grafo � nulo
    if (G == NULL) return false;

    // Chama a fun��o ExistVertice para verificar se o v�rtice existe na lista de v�rtices do grafo
    return ExistVertice(G->inicioGraph, idVertice);
}
#pragma endregion


#pragma region Mostra o grafo, exibindo todos os v�rtices e suas adjac�ncias.
/**
 * Mostra o grafo, exibindo todos os v�rtices e suas adjac�ncias.
 *
 * @param Gr O ponteiro para o grafo a ser mostrado.
 * @return true se o grafo foi mostrado com sucesso; false caso contr�rio.
 */
bool ShowGraph2(Graph* Gr)
{
    // Verifica se o grafo � nulo
    if (Gr == NULL) return false;

    // Chama a fun��o ShowGraph para mostrar o grafo
    ShowGraph(Gr->inicioGraph);

    // Retorna true para indicar que o grafo foi mostrado com sucesso
    return true;
}
#pragma endregion


#pragma region  Destr�i um grafo, liberando toda a mem�ria alocada para seus v�rtices e adjac�ncias.
/**
 * Destr�i um grafo, liberando toda a mem�ria alocada para seus v�rtices e adjac�ncias.
 *
 * @param G Apontador para o grafo a ser destru�do.
 * @param res Apontador para uma vari�vel bool onde ser� armazenado o resultado da opera��o.
 *            Ser� definido como verdadeiro se a destrui��o for bem-sucedida, ou falso caso contr�rio.
 * @return Retorna NULL ap�s destruir o grafo.
 */
Graph* DestroyGraph(Graph* G, bool* res)
{
    if (G == NULL) 
    {
        *res = false;
        return NULL;
    }

    // Loop para percorrer todos os v�rtices
    Node* currentVert = G->inicioGraph;
    while (currentVert != NULL) 
    {
        Node* nextVert = currentVert->nextVertice;

        // Loop para percorrer todas as adjac�ncias de cada v�rtice
        Adjacent* currentAdj = currentVert->nextAdjacent;
        while (currentAdj != NULL) 
        {
            Adjacent* nextAdj = currentAdj->next;
            DestroyAdjacent(currentAdj); // Libera a mem�ria da adjac�ncia
            currentAdj = nextAdj;
        }

        free(currentVert); // Libera a mem�ria do v�rtice
        currentVert = nextVert;
    }

    // Libera a mem�ria do grafo
    free(G);

    // Define o resultado como verdadeiro
    *res = true;

    // Retorna NULL (n�o h� mais grafo para apontar)
    return NULL;
}
#pragma endregion


#pragma region Insere os v�rtices e adjac�ncias no grafo com base nos dados fornecidos
/**
 * Insere os v�rtices e adjac�ncias no grafo com base nos dados fornecidos.
 *
 * @param G O grafo onde os v�rtices e adjac�ncias ser�o inseridos.
 * @param inicio O in�cio da lista de n�s representando as adjac�ncias.
 * @param vert O n�mero total de v�rtices.
 * @param adj O n�mero total de adjac�ncias.
 * @param res Apontador para uma vari�vel bool onde ser� armazenado o resultado da opera��o.
 *            Ser� definido como verdadeiro se a inser��o for bem-sucedida, ou falso caso contr�rio.
 * @return O grafo atualizado ap�s a inser��o dos v�rtices e adjac�ncias.
 */
Graph* ins_vert_adj(Graph* G, Node2* inicio, int* vert, int* adj, bool* res)
{
    // Define o resultado como verdadeiro
    *res = true;

    // Cria e insere os v�rtices no grafo
    if (*adj > *vert)
    {
        for (int i = 0; i < (*adj); i++)
        {
            // Cria um novo v�rtice
            Node* newVert = CreateVertice(i, res);
            // Insere o novo v�rtice no grafo
            G = InsertVertGraph(G, newVert, res);
            // Verifica se a opera��o de inser��o foi bem-sucedida
            if (!*res) return G;
        }
    }
    else
    {
        for (int i = 0; i < (*vert); i++)
        {
            // Cria um novo v�rtice
            Node* newVert = CreateVertice(i, res);
            // Insere o novo v�rtice no grafo
            G = InsertVertGraph(G, newVert, res);
            // Verifica se a opera��o de inser��o foi bem-sucedida
            if (!*res) return G;
        }
    }

    // Percorre a lista de adjac�ncias e insere as adjac�ncias no grafo
    Node2* current = inicio;
    for (int i = 0; i < (*vert); i++) 
    {
        for (int j = 0; j < (*adj); j++) 
        {
            if (current != NULL) 
            {
                int peso = current->peso2;
                // Insere a adjac�ncia no grafo
                G = InsertAdjaGraph(G, i, j, peso, res);
                // Verifica se a opera��o de inser��o foi bem-sucedida
                if (!*res) return G;
                current = current->next;
            }
        }
    }

    return G;
}
#pragma endregion


#pragma region Salva um grafo num ficheiro bin�rio.
/**
 * Salva um grafo num ficheiro bin�rio.
 *
 * Esta fun��o salva os dados de um grafo, incluindo seus v�rtices e arestas,
 * em um ficheiro bin�rio.
 *
 * @param G O apontador para o grafo a ser salvo.
 * @param fileName O nome do ficheiro onde o grafo ser� salvo.
 * @return Retorna 1 se a opera��o for bem-sucedida, -1 se o grafo fornecido for nulo,
 *         e -2 se houver um erro ao abrir o arquivo.
 */
int SaveGraph(Graph* G, char* fileName)
{
    if (G == NULL) return -1; // Retorna -1 se o grafo fornecido for nulo

    // Abre o ficheiro bin�rio para escrita
    FILE* fp = fopen(fileName, "wb");
    if (fp == NULL) return -2; // Retorna -2 se houver um erro ao abrir o ficheiro

    // Apontador auxiliar para percorrer os v�rtices do grafo
    Node* aux = G->inicioGraph;

    // Vari�veis auxiliares para armazenar dados dos v�rtices e arestas
    VerticeFile auxFicheiro;
    AdjFile auxAdj;
    int numAdj;

    // Loop para percorrer todos os v�rtices do grafo
    while (aux != NULL) {
        // Preenche a estrutura VerticeFile com os dados do v�rtice
        auxFicheiro.cod = aux->id;
        numAdj = 0;

        // Conta o n�mero de adjac�ncias
        Adjacent* adjAux = aux->nextAdjacent;
        while (adjAux != NULL) {
            numAdj++;
            adjAux = adjAux->next;
        }
        auxFicheiro.numAdj = numAdj;

        // Escreve o v�rtice no ficheiro
        fwrite(&auxFicheiro, sizeof(VerticeFile), 1, fp);

        // Escreve as adjac�ncias no ficheiro
        adjAux = aux->nextAdjacent;
        while (adjAux != NULL) {
            auxAdj.codOrigem = aux->id;
            auxAdj.codDestino = adjAux->id;
            auxAdj.peso = adjAux->peso;
            fwrite(&auxAdj, sizeof(AdjFile), 1, fp);
            adjAux = adjAux->next;
        }

        aux = aux->nextVertice; // Avan�a para o pr�ximo v�rtice
    }

    fclose(fp); // Fecha o ficheiro ap�s a escrita
    return 1; // Retorna 1 indicando que a opera��o foi bem-sucedida
}

#pragma endregion


#pragma region Carrega um grafo de um ficheiro bin�rio.
/**
 * Carrega um grafo de um ficheiro bin�rio.
 *
 * Esta fun��o carrega os dados de um grafo a partir de um ficheiro bin�rio.
 *
 * @param ficheiro O nome do ficheiro a ser lido.
 * @param resultado Apontador para uma vari�vel bool onde ser� armazenado o resultado da opera��o.
 *                  Ser� definido como verdadeiro se a opera��o for bem-sucedida, ou falso caso contr�rio.
 * @return Retorna um apontador para o grafo carregado, ou NULL se a opera��o falhar.
 */
Graph* LoadGraphB(const char* ficheiro, bool* resultado)
{
    // Abre o ficheiro bin�rio para leitura
    FILE* fp = fopen(ficheiro, "rb");
    if (fp == NULL) {
        *resultado = false;
        return NULL;
    }

    // Aloca mem�ria para o grafo
    Graph* grafo = (Graph*)malloc(sizeof(Graph));
    if (grafo == NULL) {
        fclose(fp);
        *resultado = false;
        return NULL;
    }

    // Inicializa o grafo
    grafo->inicioGraph = NULL;
    grafo->numeroVertices = 0;

    // L� o n�mero de v�rtices do ficheiro
    int numVertices;
    fread(&numVertices, sizeof(int), 1, fp);

    // Loop para ler os v�rtices do ficheiro
    for (int i = 0; i < numVertices; i++) 
    {
        // Aloca mem�ria para o v�rtice
        Node* vertice = (Node*)malloc(sizeof(Node));
        if (vertice == NULL) 
        {
            fclose(fp);
            DestroyGraph(grafo, resultado); // Liberta a mem�ria alocada para o grafo
            *resultado = false;
            return NULL;
        }

        // L� o ID do v�rtice do ficheiro
        fread(&vertice->id, sizeof(int), 1, fp);

        // L� o n�mero de adjac�ncias do v�rtice
        int numAdjacentes;
        fread(&numAdjacentes, sizeof(int), 1, fp);

        // Inicializa as listas de adjac�ncias do v�rtice
        vertice->nextAdjacent = NULL;
        vertice->nextVertice = NULL;

        // Loop para ler as adjac�ncias do v�rtice
        for (int j = 0; j < numAdjacentes; j++) {
            int idAdjacente;
            // L� o ID do v�rtice adjacente e o peso da aresta
            fread(&idAdjacente, sizeof(int), 1, fp);
            int peso;
            fread(&peso, sizeof(int), 1, fp);

            // Insere a adjac�ncia na lista de adjac�ncias do v�rtice
            vertice->nextAdjacent = InsertAdj(vertice->nextAdjacent, idAdjacente, peso);
        }

        // Insere o v�rtice no grafo
        grafo = InsertVertGraph(grafo, vertice, resultado);
        if (*resultado == false) {
            fclose(fp);
            DestroyGraph(grafo, resultado); // Liberta a mem�ria alocada para o grafo
            return NULL;
        }
    }

    fclose(fp);
    *resultado = true;
    return grafo;
}
#pragma endregion


#pragma region Encontra um v�rtice em um grafo com base no seu ID.
/**
 * Encontra um v�rtice em um grafo com base no seu ID.
 *
 * @param g O apontador para o grafo onde ser� feita a busca.
 * @param cod O ID do v�rtice a ser encontrado.
 * @return Retorna um apontador para o v�rtice encontrado, ou NULL se n�o for encontrado.
 * @author lufer
 */
Node* FindVerticeId(Graph* g, int cod)
{
    Node* aux = g->inicioGraph; // Inicializa o apontador auxiliar para o in�cio do grafo
    while (aux != NULL) { // Percorre a lista de v�rtices do grafo
        if (aux->id == cod) // Verifica se o ID do v�rtice atual � igual ao ID procurado
            return aux; // Retorna o apontador para o v�rtice encontrado
        aux = aux->nextVertice; // Avan�a para o pr�ximo v�rtice na lista
    }
    return NULL; // Retorna NULL se o v�rtice n�o for encontrado
}

#pragma endregion   


#pragma region Limpa o estado "visitado" de todos os v�rtices do grafo.
/**
 * @brief Limpa o estado "visitado" de todos os v�rtices do grafo.
 *
 * Esta fun��o percorre todos os v�rtices do grafo e define o estado "visitado"
 * de cada v�rtice como falso.
 *
 * @param g O ponteiro para o grafo onde o estado "visitado" ser� limpo.
 * @return Retorna um ponteiro para o grafo modificado.
 * @author lufer
 */
Graph* ResetVerticesVisitados(Graph* g) {
    Node* aux = g->inicioGraph; // Inicializa o ponteiro auxiliar para o in�cio do grafo
    while (aux) { // Percorre a lista de v�rtices do grafo
        aux->visitado = false; // Define o estado "visitado" do v�rtice como falso
        aux = aux->nextVertice; // Avan�a para o pr�ximo v�rtice na lista
    }
    return g; // Retorna o ponteiro para o grafo modificado
}
#pragma endregion   


#pragma region ALGORITMOS

/**
 * @brief Conta o n�mero de caminhos poss�veis entre dois v�rtices num grafo.
 *
 * Esta fun��o calcula o n�mero de caminhos poss�veis entre dois v�rtices
 * num grafo n�o direcionado.
 *
 * @param g O apontador para o grafo onde ser� feita a contagem de caminhos.
 * @param src O ID do v�rtice de origem.
 * @param dst O ID do v�rtice de destino.
 * @param pathCount O n�mero atual de caminhos contados.
 * @return O n�mero total de caminhos poss�veis entre os v�rtices de origem e destino.
 * @author lufer
 */
int CountPaths(Graph* g, int src, int dst, int pathCount)
{
    if (g == NULL) return 0; // Retorna 0 se o grafo fornecido for nulo

    if (src == dst) return (++pathCount); // Retorna o n�mero de caminhos incrementado se a origem for igual ao destino

    Node* aux = FindVerticeId(g, src); // Encontra o v�rtice de origem no grafo
    if (aux == NULL) return pathCount; // Retorna o n�mero de caminhos se a origem n�o for encontrada no grafo

    aux->visitado = true; // Marca o v�rtice de origem como visitado

    Adjacent* hAdj = aux->nextAdjacent; // Apontador para a lista de adjac�ncias do v�rtice de origem
    while (hAdj) { // Percorre todas as adjac�ncias do v�rtice de origem
        Node* v = FindVerticeId(g, hAdj->id); // Encontra o v�rtice adjacente no grafo
        if (v && !v->visitado) { // Verifica se o v�rtice adjacente existe e n�o foi visitado
            pathCount = CountPaths(g, hAdj->id, dst, pathCount); // Chamada recursiva para contar caminhos a partir do v�rtice adjacente
        }
        hAdj = hAdj->next; // Avan�a para a pr�xima adjac�ncia do v�rtice de origem
    }

    aux->visitado = false; // Desmarca o v�rtice de origem para permitir outros caminhos
    return pathCount; // Retorna o n�mero total de caminhos poss�veis entre os v�rtices de origem e destino
}


/**
 * @brief Conta o n�mero de caminhos poss�veis entre dois v�rtices num grafo.
 *
 * Esta fun��o conta o n�mero de caminhos poss�veis entre dois v�rtices num grafo
 * n�o direcionado, utilizando uma fun��o auxiliar para reiniciar o estado "visitado"
 * de todos os v�rtices antes de iniciar a contagem de caminhos. � uma fun��o recursiva.
 *
 * @param g O apontador para o grafo onde ser� feita a contagem de caminhos.
 * @param src O ID do v�rtice de origem.
 * @param dest O ID do v�rtice de destino.
 * @return O n�mero total de caminhos poss�veis entre os v�rtices de origem e destino.
 * @author lufer
 */
int CountPathsVertices(Graph* g, int src, int dest)
{
    ResetVerticesVisitados(g); // Reinicia o estado "visitado" de todos os v�rtices do grafo
    return CountPaths(g, src, dest, 0); // Chama a fun��o CountPaths para contar os caminhos entre os v�rtices
}


/**
 * @brief Busca em Profundidade Recursiva.
 *
 * Esta fun��o verifica se existe um caminho entre dois v�rtices num grafo,
 * utilizando o algoritmo de busca em profundidade (Depth-First Search - DFS) de forma recursiva.
 *
 * @param g O apontador para o grafo onde ser� realizada a busca.
 * @param origem O ID do v�rtice de origem.
 * @param dest O ID do v�rtice de destino.
 * @return Retorna true se existir um caminho entre os v�rtices de origem e destino, false caso contr�rio.
 * @author lufer
 */
bool DepthFirstSearchRec(Graph* g, int origem, int dest) {
    if (origem == dest) return true; // Retorna true se a origem for igual ao destino  

    Node* aux = FindVerticeId(g, origem); // Encontra o v�rtice de origem no grafo
    if (aux == NULL) return false; // Retorna false se a origem n�o for encontrada no grafo

    aux->visitado = true; // Marca o v�rtice de origem como visitado

    Adjacent* hAdj = aux->nextAdjacent; // Apontador para a lista de adjac�ncias do v�rtice de origem
    while (hAdj) { // Percorre todas as adjac�ncias do v�rtice de origem
        Node* v = FindVerticeId(g, hAdj->id); // Encontra o v�rtice adjacente no grafo
        if (v && !v->visitado) { // Verifica se o v�rtice adjacente existe e n�o foi visitado
            if (DepthFirstSearchRec(g, hAdj->id, dest)) { // Chamada recursiva para verificar se h� um caminho entre o v�rtice adjacente e o destino
                return true; // Retorna true se um caminho for encontrado
            }
        }
        hAdj = hAdj->next; // Avan�a para a pr�xima adjac�ncia do v�rtice de origem
    }

    return false; // Retorna false se nenhum caminho for encontrado
}


/**
 * @brief Algoritmo de Dijkstra.
 *
 * Este algoritmo calcula o caminho mais longo de um v�rtice inicial para todos os outros v�rtices em um grafo ponderado n�o direcionado.
 *
 * @param g O apontador para o grafo.
 * @param n O n�mero total de v�rtices no grafo.
 * @param v O v�rtice inicial para o qual ser� calculado o caminho mais longo.
 * @return Retorna uma estrutura `Best` contendo o caminho mais longo e os v�rtices predecessores para cada v�rtice no grafo.
 * @author lufer
 */
Best BestPath(Graph* g, int n, int v) {
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode;

    // Inicializa a matriz de custos com MAXDISTANCE
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = MAXDISTANCE;

    // Preenche a matriz de custos com os pesos das adjac�ncias
    Node* aux = g->inicioGraph;
    while (aux) {
        Adjacent* auxAdj = aux->nextAdjacent;
        while (auxAdj) {
            cost[aux->id][auxAdj->id] = auxAdj->peso;
            auxAdj = auxAdj->next;
        }
        aux = aux->nextVertice;
    }

    // Inicializa distance, pred e visited
    for (int i = 0; i < n; i++) {
        distance[i] = cost[v][i];
        pred[i] = v;
        visited[i] = 0;
    }

    distance[v] = 0;
    visited[v] = 1;
    count = 1;

    while (count < n - 1) {
        mindistance = MAXDISTANCE;

        
        for (int i = 0; i < n; i++) {
            if (distance[i] > mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

      
        visited[nextnode] = 1;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (mindistance + cost[nextnode][i] > distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }

    // Prepara o resultado
    Best b;
    for (int i = 0; i < n; i++) {
        b.anteriores[i] = pred[i];
        b.distance[i] = distance[i];
    }
    return b;
}

/**
 * @brief Mostra todos os caminhos mais longos a partir de um v�rtice inicial.
 *
 * Este programa imprime todos os caminhos mais longos a partir de um v�rtice inicial,
 * usando as informa��es fornecidas pela estrutura `Best`, que cont�m os caminhos mais longos
 * e os v�rtices predecessores para cada v�rtice no grafo.
 *
 * @param b A estrutura `Best` contendo os caminhos mais longos e os v�rtices predecessores.
 * @param n O n�mero total de v�rtices no grafo.
 * @param v O v�rtice inicial a partir do qual os caminhos ser�o mostrados.
 * @return Void (sem retorno).
 */
void ShowAllPath(Best b, int n, int v) 
{ 
    printf("Peso m�ximo a partir do vertice %d\n", v);
    int j;
    for (int i = 0; i < n; i++) 
    {
        if (i != v) 
        {
           
            printf("\n\nPeso at� ao vertice %d = %d", i, b.distance[i]);
            printf("\nCaminho = %d", i);

            j = i;
            do 
            {
                j = b.anteriores[j];
                printf(" <- %d", j);
            } while (j != v);
        }
    }
}

#pragma endregion