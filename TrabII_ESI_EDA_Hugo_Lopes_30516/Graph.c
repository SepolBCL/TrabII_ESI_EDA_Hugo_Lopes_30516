/**
 * @file   Graph.c
 * @brief  Implementação das funções relacionadas a grafos.
 *
 * Este ficheiro contém a implementação das funções necessárias para manipular
 * grafos, incluindo a criação, manipulação e liberação de memória.
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
* @param totV O número total de vértices do grafo.
* @param res Apontador para um booleano que indica se a criação foi bem - sucedida.
* @return Um apontador para o novo grafo criado, ou NULL se a alocação de memória falhar ou totV for inválido.
*/
Graph* CreateGraph(int *totV, bool* res)
{
   
    *res = false;
    // Verifica se o número total de vértices é válido
    if ((*totV) <= 0) return NULL;
    

    // Aloca memória para o grafo
    Graph* aux = (Graph*)malloc(sizeof(Graph));

    // Verifica se a alocação de memória foi bem-sucedida
    if (aux == NULL) return NULL;
    

    // Inicialização do grafo
    aux->inicioGraph = NULL;
    aux->numeroVertices = 0;
    aux->totVertices = (*totV);

    *res = true; // Indica que a criação do grafo foi bem-sucedida
    return aux; // Retorna o grafo criado
}
#pragma endregion


#pragma region Insere um novo vértice no grafo.
/**
*Insere um novo vértice no grafo.
*
* @param G O grafo no qual o vértice será inserido.
* @param id O ID do vértice a ser inserido.
* @param res Um apontador para um inteiro que indica o resultado da operação.
* Se a operação for bem - sucedida, res deve ser 1. Caso contrário,
* deve conter um código de erro específico.
* @return O apontador para o grafo atualizado, ou NULL em caso de erro.
*/
Graph* InsertVertGraph(Graph* G, Node* new, bool* res)
{
    
    *res = false;

    // Verifica se o grafo é válido
    if (G == NULL)
    {
        *res = false; // Código de erro: Grafo não válido
        return NULL;
    }

    // Verifica se o vértice já existe no grafo
    if (ExistVertice(G->inicioGraph, new->id))
    {
        *res = false; // Código de erro: Vértice já existe no grafo
        return G;
    }

    // Insere o vértice no grafo
    G->inicioGraph = InsertVertice(G->inicioGraph, new, res);
    if (G->inicioGraph == NULL)
    {
        *res = false; // Código de erro: Falha ao inserir vértice no grafo
        return G;
    }
    else G->numeroVertices++; // Incrementa o número de vértices no grafo
    

    // Retorna o grafo atualizado
    return G;
}
#pragma endregion


#pragma region Insere uma adjacência entre dois vértices no grafo.
/**
 * Insere uma adjacência entre dois vértices no grafo.
 *
 * @param G O grafo no qual a adjacência será inserida.
 * @param idOrigin O ID do vértice de origem.
 * @param idDestiny O ID do vértice de destino.
 * @param res Um apontador para um booleano que indica se a operação foi bem-sucedida.
 * @return O apontador para o grafo atualizado, ou NULL em caso de erro.
 */
Graph* InsertAdjaGraph(Graph* G, int idOrigin, int idDestiny,int peso, bool* res)
{
    *res = false;
    // Verifica se o grafo é nulo ou se a lista de vértices está vazia
    if (G == NULL || G->inicioGraph == NULL) return NULL;

    // Encontra os nós correspondentes no grafo
    Node* originNode = WhereIsVertice(G->inicioGraph, idOrigin);
    if (originNode == NULL) return G;
    Node* destinyNode = WhereIsVertice(G->inicioGraph, idDestiny);
    if (destinyNode == NULL) return G;

    // Insere a adjacência
    originNode->nextAdjacent = InsertAdj(originNode->nextAdjacent, idDestiny,peso);

    *res = true;
    return G;
}
#pragma endregion


#pragma region Remove uma adjacência entre dois vértices no grafo.
/**
 * Remove uma adjacência entre dois vértices no grafo.
 *
 * @param G O grafo no qual a adjacência será removida.
 * @param origin O ID do vértice de origem.
 * @param destiny O ID do vértice de destino.
 * @param res Um apontador para um booleano que indica se a operação foi bem-sucedida.
 * @return O apontador para o grafo atualizado, ou NULL em caso de erro.
 */
Graph* DeleteAdjGraph(Graph* G, int origin, int destiny, bool* res)
{
    *res = false;

    // Verifica se o grafo é nulo ou se a lista de vértices está vazia
    if (G == NULL || G->inicioGraph == NULL) return NULL;

    // Encontra os nós correspondentes no grafo
    Node* originNode = WhereIsVertice(G->inicioGraph, origin);
    if (originNode == NULL) return G;
    Node* destinyNode = WhereIsVertice(G->inicioGraph, destiny);
    if (destinyNode == NULL) return G;

    // Remove a adjacência, se existir
    originNode->nextAdjacent = DeleteAdj(originNode->nextAdjacent, destiny,res);

    *res = true;
    return G;
}
#pragma endregion


#pragma region Encontra um vértice com o ID especificado em um grafo.
/**
 * Encontra um vértice com o ID especificado em um grafo.
 *
 * @param G O apontador para o grafo onde o vértice será procurado.
 * @param idVertice O ID do vértice a ser encontrado.
 * @return Um apontador para o vértice encontrado, se existir; NULL caso contrário.
 */
Graph* WhereIsVertGraph(Graph* G, int idVertice)
{
    // Verifica se o grafo é nulo
    if (G == NULL) return NULL;
    

    // Chama a função WhereIsVertice para procurar o vértice na lista de vértices do grafo
    return (WhereIsVertice(G->inicioGraph, idVertice));
}

#pragma endregion


#pragma region Remove um vértice e todas as suas adjacências de um grafo.
/**
 * Remove um vértice e todas as suas adjacências de um grafo.
 *
 * @param g O apontador para o grafo onde o vértice será removido.
 * @param codVertice O código do vértice a ser removido.
 * @param res O apontador para uma variável que armazenará o resultado da operação.
 * @return O apontador para o grafo atualizado após a remoção do vértice e suas adjacências.
 */
Graph* DeleteVertGraph(Graph* G, int codVertice, bool* res)
{
    // Inicializa o resultado como falso
    *res = false;

    // Verifica se o grafo é nulo
    if (G == NULL) return NULL;

    // Remove o vértice da lista de vértices do grafo
    G->inicioGraph = DeleteVertice(G->inicioGraph, codVertice, res);

    // Remove todas as adjacências relacionadas ao vértice removido
    G->inicioGraph = DeleteAllAdjVert(G->inicioGraph,codVertice, res);

    // Verifica se a remoção foi bem-sucedida
    if (*res == true) G->numeroVertices--;
    

    // Retorna o apontador para o grafo atualizado após a remoção do vértice e suas adjacências
    return G;
}

#pragma endregion


#pragma region Verifica se um vértice com o ID especificado existe em um grafo.
/**
 * Verifica se um vértice com o ID especificado existe em um grafo.
 *
 * @param inicio O apontador para o início do grafo onde o vértice será procurado.
 * @param idVertice O ID do vértice a ser verificado.
 * @return true se o vértice existir no grafo; false caso contrário.
 */
bool ExistVertGraph(Graph* G, int idVertice)
{
    // Verifica se o grafo é nulo
    if (G == NULL) return false;

    // Chama a função ExistVertice para verificar se o vértice existe na lista de vértices do grafo
    return ExistVertice(G->inicioGraph, idVertice);
}
#pragma endregion


#pragma region Mostra o grafo, exibindo todos os vértices e suas adjacências.
/**
 * Mostra o grafo, exibindo todos os vértices e suas adjacências.
 *
 * @param Gr O ponteiro para o grafo a ser mostrado.
 * @return true se o grafo foi mostrado com sucesso; false caso contrário.
 */
bool ShowGraph2(Graph* Gr)
{
    // Verifica se o grafo é nulo
    if (Gr == NULL) return false;

    // Chama a função ShowGraph para mostrar o grafo
    ShowGraph(Gr->inicioGraph);

    // Retorna true para indicar que o grafo foi mostrado com sucesso
    return true;
}
#pragma endregion


#pragma region  Destrói um grafo, liberando toda a memória alocada para seus vértices e adjacências.
/**
 * Destrói um grafo, liberando toda a memória alocada para seus vértices e adjacências.
 *
 * @param G Apontador para o grafo a ser destruído.
 * @param res Apontador para uma variável bool onde será armazenado o resultado da operação.
 *            Será definido como verdadeiro se a destruição for bem-sucedida, ou falso caso contrário.
 * @return Retorna NULL após destruir o grafo.
 */
Graph* DestroyGraph(Graph* G, bool* res)
{
    if (G == NULL) 
    {
        *res = false;
        return NULL;
    }

    // Loop para percorrer todos os vértices
    Node* currentVert = G->inicioGraph;
    while (currentVert != NULL) 
    {
        Node* nextVert = currentVert->nextVertice;

        // Loop para percorrer todas as adjacências de cada vértice
        Adjacent* currentAdj = currentVert->nextAdjacent;
        while (currentAdj != NULL) 
        {
            Adjacent* nextAdj = currentAdj->next;
            DestroyAdjacent(currentAdj); // Libera a memória da adjacência
            currentAdj = nextAdj;
        }

        free(currentVert); // Libera a memória do vértice
        currentVert = nextVert;
    }

    // Libera a memória do grafo
    free(G);

    // Define o resultado como verdadeiro
    *res = true;

    // Retorna NULL (não há mais grafo para apontar)
    return NULL;
}
#pragma endregion


#pragma region Insere os vértices e adjacências no grafo com base nos dados fornecidos
/**
 * Insere os vértices e adjacências no grafo com base nos dados fornecidos.
 *
 * @param G O grafo onde os vértices e adjacências serão inseridos.
 * @param inicio O início da lista de nós representando as adjacências.
 * @param vert O número total de vértices.
 * @param adj O número total de adjacências.
 * @param res Apontador para uma variável bool onde será armazenado o resultado da operação.
 *            Será definido como verdadeiro se a inserção for bem-sucedida, ou falso caso contrário.
 * @return O grafo atualizado após a inserção dos vértices e adjacências.
 */
Graph* ins_vert_adj(Graph* G, Node2* inicio, int* vert, int* adj, bool* res)
{
    // Define o resultado como verdadeiro
    *res = true;

    // Cria e insere os vértices no grafo
    if (*adj > *vert)
    {
        for (int i = 0; i < (*adj); i++)
        {
            // Cria um novo vértice
            Node* newVert = CreateVertice(i, res);
            // Insere o novo vértice no grafo
            G = InsertVertGraph(G, newVert, res);
            // Verifica se a operação de inserção foi bem-sucedida
            if (!*res) return G;
        }
    }
    else
    {
        for (int i = 0; i < (*vert); i++)
        {
            // Cria um novo vértice
            Node* newVert = CreateVertice(i, res);
            // Insere o novo vértice no grafo
            G = InsertVertGraph(G, newVert, res);
            // Verifica se a operação de inserção foi bem-sucedida
            if (!*res) return G;
        }
    }

    // Percorre a lista de adjacências e insere as adjacências no grafo
    Node2* current = inicio;
    for (int i = 0; i < (*vert); i++) 
    {
        for (int j = 0; j < (*adj); j++) 
        {
            if (current != NULL) 
            {
                int peso = current->peso2;
                // Insere a adjacência no grafo
                G = InsertAdjaGraph(G, i, j, peso, res);
                // Verifica se a operação de inserção foi bem-sucedida
                if (!*res) return G;
                current = current->next;
            }
        }
    }

    return G;
}
#pragma endregion


#pragma region Salva um grafo num ficheiro binário.
/**
 * Salva um grafo num ficheiro binário.
 *
 * Esta função salva os dados de um grafo, incluindo seus vértices e arestas,
 * em um ficheiro binário.
 *
 * @param G O apontador para o grafo a ser salvo.
 * @param fileName O nome do ficheiro onde o grafo será salvo.
 * @return Retorna 1 se a operação for bem-sucedida, -1 se o grafo fornecido for nulo,
 *         e -2 se houver um erro ao abrir o arquivo.
 */
int SaveGraph(Graph* G, char* fileName)
{
    if (G == NULL) return -1; // Retorna -1 se o grafo fornecido for nulo

    // Abre o ficheiro binário para escrita
    FILE* fp = fopen(fileName, "wb");
    if (fp == NULL) return -2; // Retorna -2 se houver um erro ao abrir o ficheiro

    // Apontador auxiliar para percorrer os vértices do grafo
    Node* aux = G->inicioGraph;

    // Variáveis auxiliares para armazenar dados dos vértices e arestas
    VerticeFile auxFicheiro;
    AdjFile auxAdj;
    int numAdj;

    // Loop para percorrer todos os vértices do grafo
    while (aux != NULL) {
        // Preenche a estrutura VerticeFile com os dados do vértice
        auxFicheiro.cod = aux->id;
        numAdj = 0;

        // Conta o número de adjacências
        Adjacent* adjAux = aux->nextAdjacent;
        while (adjAux != NULL) {
            numAdj++;
            adjAux = adjAux->next;
        }
        auxFicheiro.numAdj = numAdj;

        // Escreve o vértice no ficheiro
        fwrite(&auxFicheiro, sizeof(VerticeFile), 1, fp);

        // Escreve as adjacências no ficheiro
        adjAux = aux->nextAdjacent;
        while (adjAux != NULL) {
            auxAdj.codOrigem = aux->id;
            auxAdj.codDestino = adjAux->id;
            auxAdj.peso = adjAux->peso;
            fwrite(&auxAdj, sizeof(AdjFile), 1, fp);
            adjAux = adjAux->next;
        }

        aux = aux->nextVertice; // Avança para o próximo vértice
    }

    fclose(fp); // Fecha o ficheiro após a escrita
    return 1; // Retorna 1 indicando que a operação foi bem-sucedida
}

#pragma endregion


#pragma region Carrega um grafo de um ficheiro binário.
/**
 * Carrega um grafo de um ficheiro binário.
 *
 * Esta função carrega os dados de um grafo a partir de um ficheiro binário.
 *
 * @param ficheiro O nome do ficheiro a ser lido.
 * @param resultado Apontador para uma variável bool onde será armazenado o resultado da operação.
 *                  Será definido como verdadeiro se a operação for bem-sucedida, ou falso caso contrário.
 * @return Retorna um apontador para o grafo carregado, ou NULL se a operação falhar.
 */
Graph* LoadGraphB(const char* ficheiro, bool* resultado)
{
    // Abre o ficheiro binário para leitura
    FILE* fp = fopen(ficheiro, "rb");
    if (fp == NULL) {
        *resultado = false;
        return NULL;
    }

    // Aloca memória para o grafo
    Graph* grafo = (Graph*)malloc(sizeof(Graph));
    if (grafo == NULL) {
        fclose(fp);
        *resultado = false;
        return NULL;
    }

    // Inicializa o grafo
    grafo->inicioGraph = NULL;
    grafo->numeroVertices = 0;

    // Lê o número de vértices do ficheiro
    int numVertices;
    fread(&numVertices, sizeof(int), 1, fp);

    // Loop para ler os vértices do ficheiro
    for (int i = 0; i < numVertices; i++) 
    {
        // Aloca memória para o vértice
        Node* vertice = (Node*)malloc(sizeof(Node));
        if (vertice == NULL) 
        {
            fclose(fp);
            DestroyGraph(grafo, resultado); // Liberta a memória alocada para o grafo
            *resultado = false;
            return NULL;
        }

        // Lê o ID do vértice do ficheiro
        fread(&vertice->id, sizeof(int), 1, fp);

        // Lê o número de adjacências do vértice
        int numAdjacentes;
        fread(&numAdjacentes, sizeof(int), 1, fp);

        // Inicializa as listas de adjacências do vértice
        vertice->nextAdjacent = NULL;
        vertice->nextVertice = NULL;

        // Loop para ler as adjacências do vértice
        for (int j = 0; j < numAdjacentes; j++) {
            int idAdjacente;
            // Lê o ID do vértice adjacente e o peso da aresta
            fread(&idAdjacente, sizeof(int), 1, fp);
            int peso;
            fread(&peso, sizeof(int), 1, fp);

            // Insere a adjacência na lista de adjacências do vértice
            vertice->nextAdjacent = InsertAdj(vertice->nextAdjacent, idAdjacente, peso);
        }

        // Insere o vértice no grafo
        grafo = InsertVertGraph(grafo, vertice, resultado);
        if (*resultado == false) {
            fclose(fp);
            DestroyGraph(grafo, resultado); // Liberta a memória alocada para o grafo
            return NULL;
        }
    }

    fclose(fp);
    *resultado = true;
    return grafo;
}
#pragma endregion


#pragma region Encontra um vértice em um grafo com base no seu ID.
/**
 * Encontra um vértice em um grafo com base no seu ID.
 *
 * @param g O apontador para o grafo onde será feita a busca.
 * @param cod O ID do vértice a ser encontrado.
 * @return Retorna um apontador para o vértice encontrado, ou NULL se não for encontrado.
 * @author lufer
 */
Node* FindVerticeId(Graph* g, int cod)
{
    Node* aux = g->inicioGraph; // Inicializa o apontador auxiliar para o início do grafo
    while (aux != NULL) { // Percorre a lista de vértices do grafo
        if (aux->id == cod) // Verifica se o ID do vértice atual é igual ao ID procurado
            return aux; // Retorna o apontador para o vértice encontrado
        aux = aux->nextVertice; // Avança para o próximo vértice na lista
    }
    return NULL; // Retorna NULL se o vértice não for encontrado
}

#pragma endregion   


#pragma region Limpa o estado "visitado" de todos os vértices do grafo.
/**
 * @brief Limpa o estado "visitado" de todos os vértices do grafo.
 *
 * Esta função percorre todos os vértices do grafo e define o estado "visitado"
 * de cada vértice como falso.
 *
 * @param g O ponteiro para o grafo onde o estado "visitado" será limpo.
 * @return Retorna um ponteiro para o grafo modificado.
 * @author lufer
 */
Graph* ResetVerticesVisitados(Graph* g) {
    Node* aux = g->inicioGraph; // Inicializa o ponteiro auxiliar para o início do grafo
    while (aux) { // Percorre a lista de vértices do grafo
        aux->visitado = false; // Define o estado "visitado" do vértice como falso
        aux = aux->nextVertice; // Avança para o próximo vértice na lista
    }
    return g; // Retorna o ponteiro para o grafo modificado
}
#pragma endregion   


#pragma region ALGORITMOS

/**
 * @brief Conta o número de caminhos possíveis entre dois vértices num grafo.
 *
 * Esta função calcula o número de caminhos possíveis entre dois vértices
 * num grafo não direcionado.
 *
 * @param g O apontador para o grafo onde será feita a contagem de caminhos.
 * @param src O ID do vértice de origem.
 * @param dst O ID do vértice de destino.
 * @param pathCount O número atual de caminhos contados.
 * @return O número total de caminhos possíveis entre os vértices de origem e destino.
 * @author lufer
 */
int CountPaths(Graph* g, int src, int dst, int pathCount)
{
    if (g == NULL) return 0; // Retorna 0 se o grafo fornecido for nulo

    if (src == dst) return (++pathCount); // Retorna o número de caminhos incrementado se a origem for igual ao destino

    Node* aux = FindVerticeId(g, src); // Encontra o vértice de origem no grafo
    if (aux == NULL) return pathCount; // Retorna o número de caminhos se a origem não for encontrada no grafo

    aux->visitado = true; // Marca o vértice de origem como visitado

    Adjacent* hAdj = aux->nextAdjacent; // Apontador para a lista de adjacências do vértice de origem
    while (hAdj) { // Percorre todas as adjacências do vértice de origem
        Node* v = FindVerticeId(g, hAdj->id); // Encontra o vértice adjacente no grafo
        if (v && !v->visitado) { // Verifica se o vértice adjacente existe e não foi visitado
            pathCount = CountPaths(g, hAdj->id, dst, pathCount); // Chamada recursiva para contar caminhos a partir do vértice adjacente
        }
        hAdj = hAdj->next; // Avança para a próxima adjacência do vértice de origem
    }

    aux->visitado = false; // Desmarca o vértice de origem para permitir outros caminhos
    return pathCount; // Retorna o número total de caminhos possíveis entre os vértices de origem e destino
}


/**
 * @brief Conta o número de caminhos possíveis entre dois vértices num grafo.
 *
 * Esta função conta o número de caminhos possíveis entre dois vértices num grafo
 * não direcionado, utilizando uma função auxiliar para reiniciar o estado "visitado"
 * de todos os vértices antes de iniciar a contagem de caminhos. É uma função recursiva.
 *
 * @param g O apontador para o grafo onde será feita a contagem de caminhos.
 * @param src O ID do vértice de origem.
 * @param dest O ID do vértice de destino.
 * @return O número total de caminhos possíveis entre os vértices de origem e destino.
 * @author lufer
 */
int CountPathsVertices(Graph* g, int src, int dest)
{
    ResetVerticesVisitados(g); // Reinicia o estado "visitado" de todos os vértices do grafo
    return CountPaths(g, src, dest, 0); // Chama a função CountPaths para contar os caminhos entre os vértices
}


/**
 * @brief Busca em Profundidade Recursiva.
 *
 * Esta função verifica se existe um caminho entre dois vértices num grafo,
 * utilizando o algoritmo de busca em profundidade (Depth-First Search - DFS) de forma recursiva.
 *
 * @param g O apontador para o grafo onde será realizada a busca.
 * @param origem O ID do vértice de origem.
 * @param dest O ID do vértice de destino.
 * @return Retorna true se existir um caminho entre os vértices de origem e destino, false caso contrário.
 * @author lufer
 */
bool DepthFirstSearchRec(Graph* g, int origem, int dest) {
    if (origem == dest) return true; // Retorna true se a origem for igual ao destino  

    Node* aux = FindVerticeId(g, origem); // Encontra o vértice de origem no grafo
    if (aux == NULL) return false; // Retorna false se a origem não for encontrada no grafo

    aux->visitado = true; // Marca o vértice de origem como visitado

    Adjacent* hAdj = aux->nextAdjacent; // Apontador para a lista de adjacências do vértice de origem
    while (hAdj) { // Percorre todas as adjacências do vértice de origem
        Node* v = FindVerticeId(g, hAdj->id); // Encontra o vértice adjacente no grafo
        if (v && !v->visitado) { // Verifica se o vértice adjacente existe e não foi visitado
            if (DepthFirstSearchRec(g, hAdj->id, dest)) { // Chamada recursiva para verificar se há um caminho entre o vértice adjacente e o destino
                return true; // Retorna true se um caminho for encontrado
            }
        }
        hAdj = hAdj->next; // Avança para a próxima adjacência do vértice de origem
    }

    return false; // Retorna false se nenhum caminho for encontrado
}


/**
 * @brief Algoritmo de Dijkstra.
 *
 * Este algoritmo calcula o caminho mais longo de um vértice inicial para todos os outros vértices em um grafo ponderado não direcionado.
 *
 * @param g O apontador para o grafo.
 * @param n O número total de vértices no grafo.
 * @param v O vértice inicial para o qual será calculado o caminho mais longo.
 * @return Retorna uma estrutura `Best` contendo o caminho mais longo e os vértices predecessores para cada vértice no grafo.
 * @author lufer
 */
Best BestPath(Graph* g, int n, int v) {
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode;

    // Inicializa a matriz de custos com MAXDISTANCE
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = MAXDISTANCE;

    // Preenche a matriz de custos com os pesos das adjacências
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
 * @brief Mostra todos os caminhos mais longos a partir de um vértice inicial.
 *
 * Este programa imprime todos os caminhos mais longos a partir de um vértice inicial,
 * usando as informações fornecidas pela estrutura `Best`, que contém os caminhos mais longos
 * e os vértices predecessores para cada vértice no grafo.
 *
 * @param b A estrutura `Best` contendo os caminhos mais longos e os vértices predecessores.
 * @param n O número total de vértices no grafo.
 * @param v O vértice inicial a partir do qual os caminhos serão mostrados.
 * @return Void (sem retorno).
 */
void ShowAllPath(Best b, int n, int v) 
{ 
    printf("Peso máximo a partir do vertice %d\n", v);
    int j;
    for (int i = 0; i < n; i++) 
    {
        if (i != v) 
        {
           
            printf("\n\nPeso até ao vertice %d = %d", i, b.distance[i]);
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